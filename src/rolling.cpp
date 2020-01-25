#include <stdio.h>
#include <cwalk.h>

int roll_file(const char *filename) {
  // On rolling the archived logs "shift down"
  // <new_file>   --> jagger.log
  // jagger.log   --> jagger.1.log
  // jagger.1.log --> jagger.2.log
  // jagger.2.log --> jagger.3.log

  // Get basename and dirname
  const char *basename;
  const char *dirname = filename;
  const char *ext;
  size_t len_basename;
  size_t len_dirname;
  size_t len_ext;
  cwk_path_get_basename(filename, &basename, &len_basename);
  cwk_path_get_dirname(dirname, &len_dirname);
  cwk_path_get_extension(filename, &ext, &len_ext);
  
  printf("--> filename: %s\n", filename);
  printf("--> basename: %.*s\n", len_basename, basename);
  printf("--> dirname : %.*s\n", len_dirname, dirname);
  printf("--> ext     : %.*s\n", len_ext, ext);
  return 0;
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
