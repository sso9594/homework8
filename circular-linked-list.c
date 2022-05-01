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
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
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
    printf("\t신승용 2019038073\n");
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

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){	// 연결리스트를 동적할당 해제하는 함수

	if(h->rlink == h)	//노드에 연결되어있는 주소가 자기자신을 가리킬 경우 연결리스트가 비어있는 것이므로
	{
		free(h);	//노드를 동적할당 해제한다
		return 1;
	}

	listNode* p = h->rlink;	//첫번째 노드의 오른쪽에 있는 노드를 p로 선언

	listNode* prev = NULL;	//이전 노드를 가리킬 노드 선언
	while(p != NULL && p != h) {	// p가 NULL이 아니고, p가 첫번째 노드로 돌아올때 까지 반복
		prev = p;	//prev를 p가 가리키는 자리로 이동
		p = p->rlink;	//p를 다음 노드로 이동
		free(prev);	//prev가 있는 노드 동적할당 해제
	}
	free(h);	//반복문이 끝났으면 첫번째 노드를 제외한 노드들이 동적할당 해제되었으므로 첫번째 노드 동적 할당해제
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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {	//마지막 순서에 노드를 추가하는 함수

	if (h == NULL) return -1;	//연결리스트가 할당이 안되어 있으면 -1 리턴

	listNode* node = (listNode*)malloc(sizeof(listNode));	//추가할 키값을 담을 노드를 동적할당
	node->key = key;	//동적할당한 노드에 키값 입력
	node->rlink = NULL;	//동적 할당한 노드에 연결할 주소값 초기화
	node->llink = NULL; //동적 할당한 노드에 연결할 주소값 초기화

	if (h->rlink == h) /* 첫 노드로 삽입 */	// 연결리스트가 비어있을 경우
	{
		h->rlink = node;	//헤더의 rlink를 추가할 노드에 연결
		h->llink = node;	//헤더의 llink를 추가할 노드에 연결
		node->rlink = h;	// 추가할 노드의 rlink를 헤더에 연결
		node->llink = h;	// 추가할 노드의 llink를 헤더에 연결
	} else {	//연결리스트가 비어있지 않다면
		h->llink->rlink = node;	//헤더의 왼쪽에 있는 노드의 rlink를 추가할 노드에 연결
		node->llink = h->llink;	//추가할 노드의 llink를 헤더에 왼쪽에 있던 노드에 연결
		h->llink = node;	//헤더의 llink를 추가할 노드에 연결
		node->rlink = h;	//추가할 노드의 rlink를 헤더에 연결
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {	//연결리스트의 마지막 노드를 삭제하는 함수

	if (h->llink == h || h == NULL)	// 연결리스트가 비어있거나 할당받지 못한 경우
	{
		printf("nothing to delete.\n");	// 에러메세지 출력
		return 1;
	}

	listNode* nodetoremove = h->llink;	//삭제할 노드를 가리킬 노드 선언하여 마지막 노드를 가리킴

	/* link 정리 */
	nodetoremove->llink->rlink = h;	//마지막 노드의 왼쪽에 있는 노드의 rlink를 헤더에 연결
	h->llink = nodetoremove->llink; //헤더의 llink를 마지막 노드의 왼쪽에 있는 노드에게 연결

	free(nodetoremove);	//모든 연결이 끊어진 마지막 노드 동적할당 해제

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {	//연결리스트 처음부분에 노드를 추가하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 추가할 키값을 담을 노드를 동적할당
	node->key = key;	//동적할당한 노드에 키값 입력
	node->rlink = NULL;	//동적 할당한 노드에 연결할 주소값 초기화
	node->llink = NULL; //동적 할당한 노드에 연결할 주소값 초기화


	node->rlink = h->rlink;	//추가할 노드의 rlink에 헤더의 오른쪽 노드 연결
	h->rlink->llink = node;	//헤더의 오른쪽에 있는 노드의 llink를 추가할 노드에 연결
	node->llink = h;	//추가할 노드의 llink 를 헤더에 연결
	h->rlink = node;	//헤더의 rlink 를 노드에 연결


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {	//연결리스트의 첫번째 노드 삭제하는 함수

	if (h == NULL || h->rlink == h)	//연결리스트가 비어있거나 할당되지 않은경우
	{
		printf("nothing to delete.\n");	//에러메세지 출력
		return 0;
	}

	listNode* nodetoremove = h->rlink;	//삭제할 노드를 가리킬 노드 선언하여 첫번째 노드를 가리킴

	/* link 정리 */
	nodetoremove->rlink->llink = h;	//첫번째 노드의 오른쪽에 있는 노드의 llink를 헤더에 연결
	h->rlink = nodetoremove->rlink;	//헤더의 rlink를 삭제할 노드의 오른쪽에 있는 노드와 연결

	free(nodetoremove);	//연결이 끊어진 첫번째 노드를 동적할당 해제

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {	//연결리스트를 역순으로 정렬하는 함수


	if(h->rlink == h || h == NULL) {	//함수가 비어있거나 할당되지 않았을 경우
		printf("nothing to invert...\n");	//에러메세지 출력
		return 0;
	}
	listNode *n = h->rlink;	//노드 n을 선언해 첫번째 노드에 연결
	listNode *trail = h;	//노드 trail을 선언해 헤더에 연결
	listNode *middle = h;	//노드 middle을 선언해 헤더에 연결

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink;	//헤더의 llink 방향을 바꿈

	while(n != NULL && n != h){
		trail = middle;	
		middle = n;	//middle 한칸 이동
		n = n->rlink;	//n 한칸 이동
		middle->rlink = trail;	//middle의 rlink를 trail에 연결(연결리스트 방향 바꾸기)
		middle->llink = n;	//middle의 llink를 n에 연결(연결리스트 방향 바꿈)
	}

	h->rlink = middle;	//헤더의 rlink 방향 바꾸기

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {	//노드를 삽입하는 함수

	if(h == NULL) return -1;	//연결리스트가 할당되지 않았다면 -1 리턴

	listNode* node = (listNode*)malloc(sizeof(listNode));	//입력할 키값을 담을 노드 선언
	node->key = key;	//키값 노드에 입력
	node->llink = node->rlink = NULL;	//노드의 연결된 주소값 초기화

	if (h->rlink == h)	//연결리스트가 비어있을 경우
	{
		insertFirst(h, key);	//insertFirst()함수를 이용해 첫번째 노드 삽입
		return 1;
	}

	listNode* n = h->rlink;//키값을 담은 노드를 삽입할 위치를 찾을 노드 선언

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) {	//n이 원형 연결리스트를 한바퀴 돌때까지 반복
		if(n->key >= key) {	//연결리스트 노드의 키값이 삽입할 키값보다 크거나 같을경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) {	//두번째 노드보다 키값이 작을경우
				insertFirst(h, key);// 첫번째 자리게 노드 삽입
			
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;	//삽입할 노드의 rlink에 n연결
				node->llink = n->llink;	//삽입할 노드의 llink에 n의 왼쪽에 있던 노드 연결
				n->llink->rlink = node;	//n의 왼쪽에 있던 노드의 rlink를 삽입할 노드에 연결
				n->llink = node;	//n의 llink에 삽입할 노드를 연결
			}
			return 0;
		}

		n = n->rlink; //n을 다음 칸으로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);	//insertLast() 함수를 이용해 마지막 위치에 노드 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {	//노드를 삭제하는 함수

	if (h->rlink == h || h == NULL)	//연결리스트가 비어있거나 할당되지 않은 경우
	{
		printf("nothing to delete.\n");	//에러메세지 출력
		return 0;
	}

	listNode* n = h->rlink;	//삭제할 노드를 가리킬 노드 선언

	while(n != NULL && n != h) {	//n이 원형리스트 한바퀴 돌때까지 반복
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);	//deleteFirst() 함수를 이용해 첫번째 노드 삭제
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h);	//deleteLast() 함수를 이용해 마지막 노드 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;	//n의 왼쪽에 있는 노드의 rlink를 n의 오른쪽 노드와 연결
				n->rlink->llink = n->llink;	//n의 오른쪽에 있는 노드의 llink를 n의 왼쪽 노드와 연결
				free(n);	//연결이 끊긴 n을 동적할당 해제
			}
			return 0;
		}

		n = n->rlink;//n을 다음 노드로 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);	//에러메세지 출력
	return 0;
}


