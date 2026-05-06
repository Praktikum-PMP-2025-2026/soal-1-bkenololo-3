#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Definisi Struktur Node
typedef struct Node {
    char id[5];
    int waktu;     
    struct Node* next;
} Node;

// 2. Definisi Struktur Queue untuk membungkus Front dan Rear
typedef struct Queue {
    Node* front;
    Node* rear;
    int size;           // Opsional: untuk melacak jumlah elemen
} Queue;

// Fungsi Inisialisasi Queue Kosong
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    return q;
}

// 3. Operasi isEmpty
int isEmpty(Queue* q) {
    return (q->front == NULL);
}

// 4. Operasi Enqueue: Menambah data ke belakang (Rear)
void enqueue(Queue* q, char value[], int waktu) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->id, value);
    newNode->waktu = waktu;
    newNode->next = NULL;

    if (q->rear == NULL) {
        // Jika antrian kosong, front dan rear ke node baru
        q->front = q->rear = newNode;
    } else {
        // Sambungkan rear lama ke node baru, lalu geser rear
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
    // printf("Enqueued: %d\n", value);
}

// 5. Operasi Dequeue: Menghapus data dari depan (Front)
// char dequeue(Queue* q) {
//     if (isEmpty(q)) {
//         printf("Queue Underflow! Antrian kosong.\n");
//         return -1; 
//     }

//     Node* temp = q->front;
//     char id[5] = temp->id;

//     q->front = q->front->next; // Geser front ke node selanjutnya

//     // Jika setelah dihapus jadi kosong, rear harus NULL
//     if (q->front == NULL) {
//         q->rear = NULL;
//     }

//     free(temp);
//     q->size--;
//     return id;
// }

// // 6. Operasi Peek: Melihat data terdepan tanpa menghapus
// char peek(Queue* q) {
//     if (isEmpty(q)) return -1;
//     return q->front->id;
// }

// 7. Operasi Display: Menampilkan seluruh isi Queue
void display(Queue* q, int totalWaktu) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    Node* curr = q->front;
    printf("ORDER");
    while (curr != NULL) {
        printf(" %s", curr->id);
        curr = curr->next;
    }
    
    printf("\nWAIT %d", totalWaktu);
}

int hitungWait(Queue* q, int N){
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return 0;
    }
    Node* curr1 = q->front;
    Node* curr2 = q->front;

    int sum = 0;
    for(int i = 0; i < N; i++){
        curr1 = curr1->next;
        for(int j = 0; j < i; j++){
            sum += curr2->waktu;
            curr2 = curr2->next;
            // if(curr2 == NULL){
            //     return 1;
            // }
        }
        curr2 = q->front;
    }
    return sum;
}

int main(){

    Queue* myQueue = createQueue();

    int N;
    scanf("%d", &N);
    char id[5];
    int waktu, totalWaktu;
  
    for(int i = 0; i < N; i++){
        scanf("%s %d", id, &waktu);
        enqueue(myQueue, id, waktu);    
        // printf("%s", id);
    }

    totalWaktu = hitungWait(myQueue, N);
    display(myQueue, totalWaktu);
}



// 4 A01 3 A02 5 A03 2 A04 4

// total waktu tunggu
// A01 : 0
// A02 : 0+3 = 3
// A03 : 0+3+5 = 8
// A04 : 0+3+5+2 = 10

// WAKTU TUNGGU TOTAL = WAKTU TUNGGU A01 + A02 + A03 + A04 + …

