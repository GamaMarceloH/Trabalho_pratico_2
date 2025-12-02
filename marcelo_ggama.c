#include <stdio.h>
#include <stdlib.h>

typedef struct listNode_s {
    int                 val;
    struct listNode_s * next;
} listNode_t;

/*
====================
PrintList
Imprime a lista no terminal
====================
*/
void PrintList(listNode_t * head) {
    while (head != NULL) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

/*
====================
Append
Adiciona nó ao final 
====================
*/
void Append(listNode_t ** head, int val) {
    listNode_t * node;
    listNode_t * temp;

    node = (listNode_t *)malloc(sizeof(listNode_t));
    
    if (node == NULL) {
        return; 
    }

    node->val = val;
    node->next = NULL;

    if (*head == NULL) {
        *head = node;
        return;
    }

    temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = node;
}

/*
====================
FindMiddle
Encontra o meio da lista
====================
*/
listNode_t *FindMiddle(listNode_t * head) {
    listNode_t * slow;
    listNode_t * fast;

    slow = head;
    fast = head;

    // "O ponteiro 'fast' avança 2 casas, o 'slow' avança 1. Quando o rápido acabar, o lento está no meio."
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

/*
====================
ReverseList
Inverte a direção dos ponteiros da lista
====================
*/
listNode_t *ReverseList(listNode_t * head) {
    listNode_t * prev;
    listNode_t * next;

    prev = NULL;
    next = NULL;

    // "Salva o próximo nó, inverto a seta para trás e avanço os ponteiros."
    while (head != NULL) {
        next = head->next;      
        head->next = prev;      
        prev = head;            
        head = next;            
    }

    // prev = nova cabeça da lista invertida."
    return prev;
}

/*
====================
ReorderList
Lógica principal de reordenação
====================
*/
void ReorderList(listNode_t * head) {
    listNode_t * middle;
    listNode_t * second;
    listNode_t * first;
    listNode_t * t1;
    listNode_t * t2;

    if (head == NULL || head->next == NULL) {
        return;
    }

    // 1: Encontra o meio da lista."
    middle = FindMiddle(head);

    // 2: Inverte a segunda metade a partir do próximo nó."
    second = ReverseList(middle->next);
    
    // 3: Corta a conexão entre as duas metades para dividir a lista."
    middle->next = NULL;

    first = head;

    // 4: Faço o Merge intercalando os nós."
    while (second != NULL) {
        // "Salvo as referências para não perder a lista."
        t1 = first->next;
        t2 = second->next;

        // "Conecta esquerda na direita e direita na esquerda."
        first->next = second;
        second->next = t1;

        // "Avança."
        first = t1;
        second = t2;
    }
}

/*
====================
FreeList 
Libera toda a memoria 
====================
*/
void FreeList(listNode_t * head) {
    listNode_t * temp;
    while (head != NULL) {
        temp = head;       // Salva o nó atual
        head = head->next; // Move para o próximo
        free(temp);        // Libera o atual
    }
}

int main() {
    listNode_t * head = NULL;
    int n, val, i;

    printf("Quantidade de elementos: ");
    scanf("%d", &n);

    if (n > 0) {
        printf("Digite os valores:\n");
        for (i = 0; i < n; i++) {
            scanf("%d", &val);
            Append(&head, val);
        }
    }

    printf("Original: ");
    PrintList(head);

    ReorderList(head);

    printf("Lista ordenada: ");
    PrintList(head);

    FreeList(head);

    return 0;
}