/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
    printf("[----- [Your Name] [Student ID] -----]\n");
    printf("\t�Ž¿� 2019038073\n");
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){	// ���Ḯ��Ʈ�� �����Ҵ� �����ϴ� �Լ�

	if(h->rlink == h)	//��忡 ����Ǿ��ִ� �ּҰ� �ڱ��ڽ��� ����ų ��� ���Ḯ��Ʈ�� ����ִ� ���̹Ƿ�
	{
		free(h);	//��带 �����Ҵ� �����Ѵ�
		return 1;
	}

	listNode* p = h->rlink;	//ù��° ����� �����ʿ� �ִ� ��带 p�� ����

	listNode* prev = NULL;	//���� ��带 ����ų ��� ����
	while(p != NULL && p != h) {	// p�� NULL�� �ƴϰ�, p�� ù��° ���� ���ƿö� ���� �ݺ�
		prev = p;	//prev�� p�� ����Ű�� �ڸ��� �̵�
		p = p->rlink;	//p�� ���� ���� �̵�
		free(prev);	//prev�� �ִ� ��� �����Ҵ� ����
	}
	free(h);	//�ݺ����� �������� ù��° ��带 ������ ������ �����Ҵ� �����Ǿ����Ƿ� ù��° ��� ���� �Ҵ�����
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {	//������ ������ ��带 �߰��ϴ� �Լ�

	if (h == NULL) return -1;	//���Ḯ��Ʈ�� �Ҵ��� �ȵǾ� ������ -1 ����

	listNode* node = (listNode*)malloc(sizeof(listNode));	//�߰��� Ű���� ���� ��带 �����Ҵ�
	node->key = key;	//�����Ҵ��� ��忡 Ű�� �Է�
	node->rlink = NULL;	//���� �Ҵ��� ��忡 ������ �ּҰ� �ʱ�ȭ
	node->llink = NULL; //���� �Ҵ��� ��忡 ������ �ּҰ� �ʱ�ȭ

	if (h->rlink == h) /* ù ���� ���� */	// ���Ḯ��Ʈ�� ������� ���
	{
		h->rlink = node;	//����� rlink�� �߰��� ��忡 ����
		h->llink = node;	//����� llink�� �߰��� ��忡 ����
		node->rlink = h;	// �߰��� ����� rlink�� ����� ����
		node->llink = h;	// �߰��� ����� llink�� ����� ����
	} else {	//���Ḯ��Ʈ�� ������� �ʴٸ�
		h->llink->rlink = node;	//����� ���ʿ� �ִ� ����� rlink�� �߰��� ��忡 ����
		node->llink = h->llink;	//�߰��� ����� llink�� ����� ���ʿ� �ִ� ��忡 ����
		h->llink = node;	//����� llink�� �߰��� ��忡 ����
		node->rlink = h;	//�߰��� ����� rlink�� ����� ����
	}

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {	//���Ḯ��Ʈ�� ������ ��带 �����ϴ� �Լ�

	if (h->llink == h || h == NULL)	// ���Ḯ��Ʈ�� ����ְų� �Ҵ���� ���� ���
	{
		printf("nothing to delete.\n");	// �����޼��� ���
		return 1;
	}

	listNode* nodetoremove = h->llink;	//������ ��带 ����ų ��� �����Ͽ� ������ ��带 ����Ŵ

	/* link ���� */
	nodetoremove->llink->rlink = h;	//������ ����� ���ʿ� �ִ� ����� rlink�� ����� ����
	h->llink = nodetoremove->llink; //����� llink�� ������ ����� ���ʿ� �ִ� ��忡�� ����

	free(nodetoremove);	//��� ������ ������ ������ ��� �����Ҵ� ����

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {	//���Ḯ��Ʈ ó���κп� ��带 �߰��ϴ� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode));	// �߰��� Ű���� ���� ��带 �����Ҵ�
	node->key = key;	//�����Ҵ��� ��忡 Ű�� �Է�
	node->rlink = NULL;	//���� �Ҵ��� ��忡 ������ �ּҰ� �ʱ�ȭ
	node->llink = NULL; //���� �Ҵ��� ��忡 ������ �ּҰ� �ʱ�ȭ


	node->rlink = h->rlink;	//�߰��� ����� rlink�� ����� ������ ��� ����
	h->rlink->llink = node;	//����� �����ʿ� �ִ� ����� llink�� �߰��� ��忡 ����
	node->llink = h;	//�߰��� ����� llink �� ����� ����
	h->rlink = node;	//����� rlink �� ��忡 ����


	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {	//���Ḯ��Ʈ�� ù��° ��� �����ϴ� �Լ�

	if (h == NULL || h->rlink == h)	//���Ḯ��Ʈ�� ����ְų� �Ҵ���� �������
	{
		printf("nothing to delete.\n");	//�����޼��� ���
		return 0;
	}

	listNode* nodetoremove = h->rlink;	//������ ��带 ����ų ��� �����Ͽ� ù��° ��带 ����Ŵ

	/* link ���� */
	nodetoremove->rlink->llink = h;	//ù��° ����� �����ʿ� �ִ� ����� llink�� ����� ����
	h->rlink = nodetoremove->rlink;	//����� rlink�� ������ ����� �����ʿ� �ִ� ���� ����

	free(nodetoremove);	//������ ������ ù��° ��带 �����Ҵ� ����

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {	//���Ḯ��Ʈ�� �������� �����ϴ� �Լ�


	if(h->rlink == h || h == NULL) {	//�Լ��� ����ְų� �Ҵ���� �ʾ��� ���
		printf("nothing to invert...\n");	//�����޼��� ���
		return 0;
	}
	listNode *n = h->rlink;	//��� n�� ������ ù��° ��忡 ����
	listNode *trail = h;	//��� trail�� ������ ����� ����
	listNode *middle = h;	//��� middle�� ������ ����� ����

	/* ���� �ٲ� ��ũ ���� */
	h->llink = h->rlink;	//����� llink ������ �ٲ�

	while(n != NULL && n != h){
		trail = middle;	
		middle = n;	//middle ��ĭ �̵�
		n = n->rlink;	//n ��ĭ �̵�
		middle->rlink = trail;	//middle�� rlink�� trail�� ����(���Ḯ��Ʈ ���� �ٲٱ�)
		middle->llink = n;	//middle�� llink�� n�� ����(���Ḯ��Ʈ ���� �ٲ�)
	}

	h->rlink = middle;	//����� rlink ���� �ٲٱ�

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {	//��带 �����ϴ� �Լ�

	if(h == NULL) return -1;	//���Ḯ��Ʈ�� �Ҵ���� �ʾҴٸ� -1 ����

	listNode* node = (listNode*)malloc(sizeof(listNode));	//�Է��� Ű���� ���� ��� ����
	node->key = key;	//Ű�� ��忡 �Է�
	node->llink = node->rlink = NULL;	//����� ����� �ּҰ� �ʱ�ȭ

	if (h->rlink == h)	//���Ḯ��Ʈ�� ������� ���
	{
		insertFirst(h, key);	//insertFirst()�Լ��� �̿��� ù��° ��� ����
		return 1;
	}

	listNode* n = h->rlink;//Ű���� ���� ��带 ������ ��ġ�� ã�� ��� ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL && n != h) {	//n�� ���� ���Ḯ��Ʈ�� �ѹ��� �������� �ݺ�
		if(n->key >= key) {	//���Ḯ��Ʈ ����� Ű���� ������ Ű������ ũ�ų� �������
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->rlink) {	//�ι�° ��庸�� Ű���� �������
				insertFirst(h, key);// ù��° �ڸ��� ��� ����
			
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;	//������ ����� rlink�� n����
				node->llink = n->llink;	//������ ����� llink�� n�� ���ʿ� �ִ� ��� ����
				n->llink->rlink = node;	//n�� ���ʿ� �ִ� ����� rlink�� ������ ��忡 ����
				n->llink = node;	//n�� llink�� ������ ��带 ����
			}
			return 0;
		}

		n = n->rlink; //n�� ���� ĭ���� �̵�
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);	//insertLast() �Լ��� �̿��� ������ ��ġ�� ��� ����
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {	//��带 �����ϴ� �Լ�

	if (h->rlink == h || h == NULL)	//���Ḯ��Ʈ�� ����ְų� �Ҵ���� ���� ���
	{
		printf("nothing to delete.\n");	//�����޼��� ���
		return 0;
	}

	listNode* n = h->rlink;	//������ ��带 ����ų ��� ����

	while(n != NULL && n != h) {	//n�� ��������Ʈ �ѹ��� �������� �ݺ�
		if(n->key == key) {
			if(n == h->rlink) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);	//deleteFirst() �Լ��� �̿��� ù��° ��� ����
			} else if (n->rlink == h){ /* ������ ����� ��� */
				deleteLast(h);	//deleteLast() �Լ��� �̿��� ������ ��� ����
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;	//n�� ���ʿ� �ִ� ����� rlink�� n�� ������ ���� ����
				n->rlink->llink = n->llink;	//n�� �����ʿ� �ִ� ����� llink�� n�� ���� ���� ����
				free(n);	//������ ���� n�� �����Ҵ� ����
			}
			return 0;
		}

		n = n->rlink;//n�� ���� ���� �̵�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);	//�����޼��� ���
	return 0;
}


