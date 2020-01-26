#include <stdio.h>
#include <time.h>
#include <cwalk.h>
#include <tinydir.h>
#include "rolling.h"

int roll_file_by_size(const char *filename) {
  // On rolling the archived logs "shift down"
  // <new_file>   --> jagger.log
  // jagger.log   --> jagger.1.log
  // jagger.1.log --> jagger.2.log
  // jagger.2.log --> jagger.3.log

  // Get basename and dirname
  // TODO: Refactor into own function; duplicated code
  const char *basename;
  const char *ext;
  size_t len_basename;
  size_t len_dirname;
  size_t len_ext;
  cwk_path_get_basename(filename, &basename, &len_basename);
  cwk_path_get_dirname(filename, &len_dirname);
  cwk_path_get_extension(filename, &ext, &len_ext);
  char dirname[len_dirname];
  strncpy(dirname, filename, len_dirname);
  dirname[len_dirname] = '\0';
  char *fname = strip_extension(basename, ext);
  // End duplicated code

  int n = count_old_logfiles(dirname, fname, ext);
  if (n < 0) {
    // Something went wrong
    return -1;
  }
  if (n == 0) {
    // No need to rotate
    return 0;
  }
  // n indicates the number of log files already presents
  char src[FILENAME_MAX];
  char dest[FILENAME_MAX];
  while (n > 0) {
    n - 1 == 0 ? 
      sprintf(src, "%s%s%s", dirname, fname, ext) :
      sprintf(src, "%s%s.%d%s", dirname, fname, n - 1, ext);
    sprintf(dest, "%s%s.%d%s", dirname, fname, n, ext);
    rename(src, dest);
    n--;
  }
  return 0;
}

int roll_file_by_day(const char *filename) {
  // Get basename and dirname
  // TODO: Refactor into own function; duplicated code
  const char *basename;
  const char *ext;
  size_t len_basename;
  size_t len_dirname;
  size_t len_ext;
  cwk_path_get_basename(filename, &basename, &len_basename);
  cwk_path_get_dirname(filename, &len_dirname);
  cwk_path_get_extension(filename, &ext, &len_ext);
  char dirname[len_dirname];
  strncpy(dirname, filename, len_dirname);
  dirname[len_dirname] = '\0';
  char *fname = strip_extension(basename, ext);
  // End duplicated code

  struct stat attr;
  stat(filename, &attr);
  char date[20];
  strftime(date, sizeof(date), "%Y-%m-%d", localtime(&attr.st_mtime));
  char dest[FILENAME_MAX];
  sprintf(dest, "%s%s.%s%s", dirname, fname, date, ext);
  rename(filename, dest);
  return 0;
}

char *strip_extension(const char *filename, const char *ext) {
  const char *s1 = strstr(filename, ext);
  size_t len = s1 - filename;
  char *s2 = (char *)malloc(len + 1);
  memcpy(s2, filename, len);
  s2[len] = 0;
  return s2;
}

int count_old_logfiles(const char *logdir, const char *logname, const char *logext){
  tinydir_dir dir;
  if (tinydir_open_sorted(&dir, logdir) == -1) {
    tinydir_close(&dir);
    return -1;
  }

  int n = 0;
  for (int i = 0; i < dir.n_files; i++) {
    tinydir_file file;
    if (tinydir_readfile_n(&dir, &file, i) == 0) {
      char *dot = strrchr(file.name, '.');
      // Count only file that starts with logname and ends with logext
      if (strstr(file.name, logname) == file.name && dot && !strcmp(dot, logext)) {
        n++;
      }
    }
  }
  tinydir_close(&dir);
  return n;
}
