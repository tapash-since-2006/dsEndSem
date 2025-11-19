// void bubbleSort(struct Node* head) {
//     struct Node* ptr1 = head;
//     struct Node* ptr2;

//     while (ptr1 != NULL) {
//         ptr2 = head;
//         while (ptr2->next != NULL) {
//             if (ptr2->data > ptr2->next->data) {
//                 int temp = ptr2->data;
//                 ptr2->data = ptr2->next->data;
//                 ptr2->next->data = temp;
//             }
//             ptr2 = ptr2->next;
//         }
//         ptr1 = ptr1->next;
//     }
// }


// void sortedInsert(Stack* s, int x) {
//     if (isEmpty(s) || top(s) <= x) {
//         push(s, x);
//         return;
//     }

//     int temp = pop(s);
//     sortedInsert(s, x);
//     push(s, temp);
// }

// void sortStack(Stack* s) {
//     if (!isEmpty(s)) {
//         int x = pop(s);
//         sortStack(s);
//         sortedInsert(s, x);
//     }
// }


// void sortedInsert(Stack* s, int x) {
//     if (isEmpty(s) || top(s) <= x) {
//         push(s, x);
//         return;
//     }

//     int temp = pop(s);
//     sortedInsert(s, x);
//     push(s, temp);
// }

// void sortStack(Stack* s) {
//     if (!isEmpty(s)) {
//         int x = pop(s);
//         sortStack(s);
//         sortedInsert(s, x);
//     }
// }


