#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTENT 256

typedef struct Note {
    int id;
    char content[MAX_CONTENT];
    struct Note* next;
} Note;

Note* head = NULL;
int next_id = 1;

void load_notes();
void save_notes();
void add_note();
void list_notes();
void delete_note();
void free_notes();

int main() {
    int choice;

    load_notes();

    do {
        printf("\n=== Mini Notepad ===\n");
        printf("1. Yeni not ekle\n");
        printf("2. Notları listele\n");
        printf("3. Not sil\n");
        printf("4. Çıkış\n");
        printf("Seçiminiz: ");
        scanf("%d", &choice);
        getchar(); // newline'ı yutmak için

        switch (choice) {
            case 1:
                add_note();
                break;
            case 2:
                list_notes();
                break;
            case 3:
                delete_note();
                break;
            case 4:
                save_notes();
                free_notes();
                printf("Notlar kaydedildi. Güle güle!\n");
                break;
            default:
                printf("Geçersiz seçim. Tekrar deneyin.\n");
        }

    } while (choice != 4);

    return 0;
}

void load_notes() {
    FILE* file = fopen("notes.txt", "r");
    if (!file) return;

    char buffer[MAX_CONTENT];
    int id;
    while (fscanf(file, "%d|%[^\n]\n", &id, buffer) == 2) {
        Note* new_note = (Note*)malloc(sizeof(Note));
        new_note->id = id;
        strcpy(new_note->content, buffer);
        new_note->next = head;
        head = new_note;

        if (id >= next_id) {
            next_id = id + 1;
        }
    }
    fclose(file);
}

void save_notes() {
    FILE* file = fopen("notes.txt", "w");
    if (!file) {
        printf("Dosya kaydedilemedi.\n");
        return;
    }

    Note* current = head;
    while (current) {
        fprintf(file, "%d|%s\n", current->id, current->content);
        current = current->next;
    }
    fclose(file);
}

void add_note() {
    char buffer[MAX_CONTENT];
    printf("Notunuzu girin: ");
    fgets(buffer, MAX_CONTENT, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // newline sil

    Note* new_note = (Note*)malloc(sizeof(Note));
    new_note->id = next_id++;
    strcpy(new_note->content, buffer);
    new_note->next = head;
    head = new_note;

    printf("Not eklendi (ID: %d)\n", new_note->id);
}

void list_notes() {
    if (!head) {
        printf("Henüz hiç not yok.\n");
        return;
    }

    printf("\n--- Notlar ---\n");
    Note* current = head;
    while (current) {
        printf("[%d] %s\n", current->id, current->content);
        current = current->next;
    }
}

void delete_note() {
    int target_id;
    printf("Silmek istediğiniz notun ID'sini girin: ");
    scanf("%d", &target_id);
    getchar(); // newline yut

    Note* current = head;
    Note* prev = NULL;

    while (current) {
        if (current->id == target_id) {
            if (prev)
                prev->next = current->next;
            else
                head = current->next;

            free(current);
            printf("Not silindi.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Bu ID'ye sahip bir not bulunamadı.\n");
}

void free_notes() {
    Note* current = head;
    while (current) {
        Note* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}
