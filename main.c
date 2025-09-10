#include <stdio.h>  // fgets, getchar, stdin
#include <stdlib.h> // strtol
#include <string.h> // strlen,strcmp
#include <errno.h>  // errno, ERANGE
#include <limits.h> // INT_MIN, INT_MAX, LONG_MIN, LONG_MAX
#define MAX_TASK 256
#define MAX_TASKS 100
#define FILE_NAME "tasks.txt"

typedef struct
{
    char text[MAX_TASK];
    int done; // 0 = Non termine , 1 = Termine
} Task;

Task tasks[MAX_TASKS];
int task_count = 0;
enum CMD_OF_TASKS
{
    enum_add = 1,
    enum_show_tasks = 2,
    enum_del = 3,
    enum_toggle_tasks = 4,
    enum_quite = 5,
    enum_show_mane = 6
};
int Lire_str(char *str, int N)
{
    if (str == NULL || N <= 0)
    {
        return 0; // Invalid parameters
    }

    if (fgets(str, N, stdin) == NULL)
    {
        return 0; // End of input or error
    }

    size_t len_str = strlen(str);

    // Remove trailing newline if present
    if (len_str > 0 && str[len_str - 1] == '\n')
    {
        str[len_str - 1] = '\0';
    }
    else
    {
        // Flush the remaining input
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }

    return 1; // Successful input
}
int Lire_int(int *result)
{
    char buffer[256];
    char *endptr;
    long value;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return 0;
    }

    errno = 0;
    value = strtol(buffer, &endptr, 10);

    if (errno == ERANGE && (value == LONG_MAX || value == LONG_MIN))
    {
        return 0;
    }

    if (endptr == buffer || *endptr != '\n')
    {
        return 0;
    }

    if (value < INT_MIN || value > INT_MAX)
    {
        return 0;
    }

    *result = (int)value;
    return 1;
}

// Charger les taches a partir du fichier (Load)
void load_tasks()
{
    FILE *f = fopen(FILE_NAME, "r");
    if (!f)
        return; // Aucun fichier trouve la premiere fois
    while (fscanf(f, "%d;%[^\n]\n", &tasks[task_count].done, tasks[task_count].text) == 2)
    {
        task_count++;
    }
    fclose(f);
}

// Enregistrer les taches dans le fichier (Enregistrer)void save_tasks()
void save_tasks()
{
    FILE *f = fopen(FILE_NAME, "w");
    if (!f)
    {
        perror("fopen");
        return;
    }
    for (int i = 0; i < task_count; i++)
    {
        fprintf(f, "%d;%s\n", tasks[i].done, tasks[i].text);
    }
    fclose(f);
}

// Ajouter une tache
void add_task()
{
    if (task_count >= MAX_TASKS)
    {
        printf("⚠ Vous avez atteint le nombre maximum de taches.\n");
        return;
    }
    int resultat;
    do
    {
        printf("Entrez la tache: ");
        resultat = Lire_str(tasks[task_count].text, MAX_TASK);
    } while (resultat == 0 || strlen(tasks[task_count].text) == 0);
    tasks[task_count]
        .text[strcspn(tasks[task_count].text, "\n")] = '\0';
    tasks[task_count].done = 0;
    task_count++;
    printf("Tache ajoutee!\n");
}

// Afficher les tâches
void list_tasks()
{
    if (task_count == 0)
    {
        printf("Aucune tache.\n");
        return;
    }
    printf("\n=== Liste des taches ===\n");
    for (int i = 0; i < task_count; i++)
    {
        printf("%d. [%c] %s\n", i + 1, tasks[i].done ? 'X' : '-', tasks[i].text);
    }
}

// Supprimer la tache
void delete_task()
{
    if (task_count == 0)
    {
        printf("Aucune tache a supprimer.\n");
        return;
    }
    list_tasks();
    int num, resultat;
    do
    {
        printf("Entrez le numero de la tache a supprimer: ");
        resultat = Lire_int(&num);
    } while (resultat == 0);

    if (num < 1 || num > task_count)
    {
        printf("Numero invalide.\n");
        return;
    }
    for (int i = num - 1; i < task_count - 1; i++)
    {
        tasks[i] = tasks[i + 1];
    }
    task_count--;
    printf("La tache a ete supprimee.\n");
}

// Changer le statut de la tache (terminee/non terminee)
void toggle_task()
{
    if (task_count == 0)
    {
        printf("⚠ Aucune tâche.\n");
        return;
    }
    list_tasks();

    int num, resultat;
    do
    {
        printf("Entrez le numero de la tache pour modifier son statut: ");
        resultat = Lire_int(&num);
    } while (resultat == 0);

    if (num < 1 || num > task_count)
    {
        printf("Numero invalide.\n");
        return;
    }
    tasks[num - 1].done = !tasks[num - 1].done;
    printf("Statut modifie.\n");
}

void show_man_of_cmd()
{
    printf("======================================MAN===================================================\n");
    printf("add/ADD.......: Ajouter une tache\n");
    printf("show/SHOW.....: Afficher les taches\n");
    printf("del/DEL.......: Supprimer une tache\n");
    printf("man/MAN.......: afficher le menu de commend\n");
    printf("tog/TOG.:  Basculer l'etat de la tache \n");
    printf("quite/QUITE...: Quitter (avec sauvegarde)\n");
    printf("==============================================================================================\n");
}

int cmd_to_int(char *cmd)
{

    if (strcmp(cmd, "add") == 0 || strcmp(cmd, "ADD") == 0 || strcmp(cmd, "1") == 0)
    {
        return enum_add;
    }
    else if (strcmp(cmd, "show") == 0 || strcmp(cmd, "SHOW") == 0 || strcmp(cmd, "2") == 0)
    {
        return enum_show_tasks;
    }
    else if (strcmp(cmd, "del") == 0 || strcmp(cmd, "DEL") == 0 || strcmp(cmd, "3") == 0)
    {
        return enum_del;
    }
    else if (strcmp(cmd, "tog") == 0 || strcmp(cmd, "TOG") == 0 || strcmp(cmd, "4") == 0)
    {
        return enum_toggle_tasks;
    }
    else if (strcmp(cmd, "quite") == 0 || strcmp(cmd, "QUITE") == 0 || strcmp(cmd, "5") == 0)
    {
        return enum_quite;
    }
    else if (strcmp(cmd, "man") == 0 || strcmp(cmd, "MAN") == 0 || strcmp(cmd, "6") == 0)
    {
        return enum_show_mane;
    }
    else
    {
        return -1;
    }
}
int main()
{
    char cmd[10];
    int choix, resultat;
    load_tasks(); // Charger au demarrage
    while (1)
    {
        printf("\n==== Liste des taches ====\n");
        printf("1. Ajouter une tache\n");
        printf("2. Afficher les taches\n");
        printf("3. Supprimer une tache\n");
        printf("4. Basculer l'etat de la tache \n");
        printf("5. Quitter (avec sauvegarde)\n");
        printf("6. afficher le menu de commend\n");

        do
        {
            printf("\nVotre choix : ");
            resultat = Lire_str(cmd, 10);
            choix = cmd_to_int(cmd);
        } while (resultat == 0 || (choix < enum_add || choix > enum_show_mane));
        switch (choix)
        {
        case 1:
            add_task();
            break;
        case 2:
            list_tasks();
            break;
        case 3:
            delete_task();
            break;
        case 4:
            toggle_task();
            break;
        case 5:
            save_tasks();
            printf("Sauve. Au revoir !\n");
            exit(0);
        case 6:
            show_man_of_cmd();
            break;
        default:
            printf("Choix invalide.\n");
        }
    }
    return 0;
}
