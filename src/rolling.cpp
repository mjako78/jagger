#include <stdio.h>
#include <cwalk.h>
#include <tinydir.h>
#include "rolling.h"

int roll_file(const char *filename) {
  // On rolling the archived logs "shift down"
  // <new_file>   --> jagger.log
  // jagger.log   --> jagger.1.log
  // jagger.1.log --> jagger.2.log
  // jagger.2.log --> jagger.3.log

  // Get basename and dirname
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

  printf("--> filename: %s\n", filename);
  printf("--> basename: %s\n", basename);
  printf("--> dirname : %s\n", dirname);
  printf("--> ext     : %s\n", ext);
  printf("--> fname   : %s\n", fname);


  // Get older log, if any
  // tinydir_dir dir;
  // if (tinydir_open_sorted(&dir, dirname) == -1) {
  //   return -1;
  // }
  // printf("--> getting files in %s\n", dirname);
  // for (int i = 0; i < dir.n_files; i++) {
  //   tinydir_file file;
  //   if (tinydir_readfile_n(&dir, &file, i) == 0) {
  //     printf("    %d --> %s\n", i, file.name);
  //   }
  // }
  // tinydir_close(&dir);
  int n = count_old_logfiles(dirname, fname, ext);
  printf("--> n: %d\n", n);
  if (n < 0) {
    // Something went wrong
    return -1;
  }
  if (n == 0) {
    // No need to rotate
    return 0;
  }
  // n indicates the number of log files already presents
  
  

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

int count_old_logfiles(const char *logdir, const char *logname, const char *logext) {
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

// int roll_file(const char *filename)
// {
//   // On rolling the archived logs "shift down"
//   // <new_file>   --> jagger.log
//   // jagger.log   --> jagger.1.log
//   // jagger.1.log --> jagger.2.log
//   // jagger.2.log --> jagger.3.log

//   // Check for basename and filepath
//   int dot = '.';
//   char *file_basename = basename((char *)filename);
//   char *file_ext = strrchr((char *)filename, dot);
//   size_t len = strstr((char *)filename, file_basename) - filename;
//   char *filepath = (char *)malloc(len + 1);
//   if (filepath)
//   {
//     memcpy(filepath, filename, len);
//     filepath[len] = 0;
//   }
//   printf("--> basename: %s\n", file_basename);
//   printf("--> extension: %s\n", file_ext);
//   printf("--> filepath: %s\n", filepath);

//   // Find old log files in directory
//   DIR *dir;
//   struct dirent *ent;
//   int n = 0;
//   if ((dir = opendir(filepath)) != NULL)
//   {
//     while (((ent = readdir(dir)) != NULL) && strstr(ent->d_name, file_ext))
//     {
//       n++;
//     }
//     closedir(dir);
//   }
//   int x = n;
//   char *old_logs[n];
//   if ((dir = opendir(filepath)) != NULL)
//   {
//     while (((ent = readdir(dir)) != NULL) && strstr(ent->d_name, file_ext))
//     {
//       old_logs[--n] = ent->d_name;
//     }
//     closedir(dir);
//   }
//   for (int i = 0; i < x; i++)
//   {
//     printf("--> file: %s\n", old_logs[i]);
//     // Check for counter, if any
//     char *left = strchr((char *)old_logs[i], dot);
//     char *right = strrchr((char *)old_logs[i], dot);
//     printf("... left : %s\n", left);
//     printf("... right: %s\n", right);
//     if (strcmp(left, right))
//     {
//       printf("  COUNTER!\n");
//       size_t l = strstr((char *)left, right) - left;
//       char *counter = (char *)malloc(l + 1);
//       if (counter)
//       {
//         memcpy(counter, left, l);
//         counter[l] = 0;
//       }
//       printf("  ... counter: %s\n", counter);
//     }
//     else
//     {
//       printf("  NO COUNTER!\n");
//     }
//   }

//   return 0;
// }
