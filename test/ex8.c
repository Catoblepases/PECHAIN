#include <dirent.h>
#include <stdio.h>
int main() {
    DIR *rep = opendir("./Blockchain/");
    if (rep != NULL) {
        struct dirent *dir;
        while ((dir = readdir(rep))) {
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
                printf("Chemin-du. fichier.:./Blockchain/%s.\n", dir->d_name);
            }
        }
        closedir(rep);
    }
}