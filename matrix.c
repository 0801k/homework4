#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int** create_matrix(int row, int col); //배열에 동적 할당을 받아 행렬을 생성한다
void print_matrix(int** matrix, int row, int col); //동적 할당을 받은 배열의 메모리를 해제한다
int free_matrix(int** matrix, int row, int col); // 동적 할당을 받은 배열에 임의의 값을 넣는다
int fill_data(int** matrix, int row, int col); // 임의의 값을 넣은 행렬을 출력한다
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); // 각각의 행렬을 더한다
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); // 각각의 행렬을 뺀다
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); // 특정 행렬을 전치행렬로 변환한다
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); // 각각의 행렬을 곱한다

int main()
{
    char command;
    printf("[----- [노관범]  [2020039102] -----]\n");

	int row, col; // 입력받을 행과 열
	srand(time(NULL)); 

	printf("Input row and col : "); 
	scanf("%d %d", &row, &col); // 행과 열 입력
    int** matrix_a = create_matrix(row, col); // 행렬 a를 생성한다
	int** matrix_b = create_matrix(row, col); // 행렬 b를 생선한다
    int** matrix_a_t = create_matrix(col, row); // 행렬 a의 전치행렬을 표현할 행렬을 생성한다

	printf("Matrix Created.\n"); // 성공문구를 출력한다

	if (matrix_a == NULL || matrix_b == NULL) {return -1;} // a,b가 가리키는 주소가 없을시, -1로 종료한다.

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Matrix Manipulation                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Matrix   = z           Print Matrix        = p \n");
		printf(" Add Matrix          = a           Subtract Matrix     = s \n");
		printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
		printf(" Quit                = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		
		switch(command) {
		case 'z': case 'Z': // z나 Z를 입력했을때
		    printf("Matrix Initialized\n");
			fill_data(matrix_a, row, col); // 행렬 a에 0부터 19까지의 임의 값 채우기
			fill_data(matrix_b, row, col);// 행렬 b에 0부터 19까지의 임의 값 채우기
			break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
			print_matrix(matrix_a, row, col); // 행렬 a의 값을 출력한다
			printf("matrix_b\n");
			print_matrix(matrix_b, row, col); // 행렬 b의 값을 출력한다
			break;
        case 'a': case 'A': // a나 A를 입력했을떄
			printf("Add two matrices\n");
			addition_matrix(matrix_a, matrix_b, row, col); // 행렬 a와 b의 합 나타낸 행렬 생성하고 출력, 동적 할당된 공간을 해제한다.
			break;
        case 's': case 'S': // s나 S를 입력했을떄
			printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); // 행렬 a와 b를 나타낸 행렬 생성하고 출력, 동적 할당된 공간을 해제한다.
			break;
        case 't': case 'T': // t나 T를 입력했을때
			printf("Transpose matrix_a \n");
			printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); // 
            print_matrix(matrix_a_t, col, row); // 행렬 a의 전치행렬을 출력한다.행렬 a의 전치행렬을 matrix_a_t에 넣는다
			break;
        case 'm': case 'M': // m이나 M을 입력했을때
			printf("Multiply matrix_a with transposed matrix_a \n");
			transpose_matrix(matrix_a, matrix_a_t, col, row); // 행렬 a의 전치행렬을 출력한다.행렬 a의 전치행렬을 matrix_a_t에 넣는다
            multiply_matrix(matrix_a, matrix_a_t, row, col); // 행렬 a와 a의 곱 나타낸 행렬 생성하고 출력, 동적 할당된 공간을 해제한다.
			break;
        case 'q': case 'Q': // q나 Q를 입력했을때
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); // martrix_a_t의 공간을 해제한다
            free_matrix(matrix_a, row, col); // 행렬 a의 공간을 해제한다
            free_matrix(matrix_b, row, col); // 행렬 b의 공간을 해제한다
			break;
		default: // 할당되지 않은 명령어를 입력했을때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 문구를 출력한다
			break;
		}

	}while(command != 'q' && command != 'Q'); // q나 Q를 입력할 때까지 반복한다

	return 1; // 종료한다
}

/* create a 2d array whose size is row x col using malloc() */
int** create_matrix(int row, int col) // 2차원 배열 행렬을 생성한다
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) // row나 col이 0이하이면
	 {
		printf("Check the size of row and col!\n"); // 행과 열 확인하라는 문구를 출력한다
		return NULL;
	}

	int** matrix = (int**)malloc(sizeof(int*) * row); // 공간 생성하고 주소를 matrix에 할당한다
	for (int r = 0; r < row; r++) 
	 {
		matrix[r] = (int*)malloc(sizeof(int) * col); // 행의 개수만큼 만들고, 공간들 주소를 접근하는 공간에 할당한다
	}

	/* Check post conditions */
	if (matrix == NULL) // 주소가 없을 경우 
	{
		printf("Memory Allocation Failed.\n"); // 동적 메모리 할당 실패 문구를 출력한다
		return NULL;
	}

	return matrix; // 생성된 주소를 반환한다
}

/* print matrix whose size is row x col */
void print_matrix(int** matrix, int row, int col) // matrix의 모든 성분을 출력한다
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) // row나 col이 0이하이면
	{
		printf("Check the size of row and col!\n"); // 행과 열 확인하라는 문구를 출력한다
		return;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) // 첫번째 행부터 마지막 행까지 진행한다 
	{
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // 첫번째 열부터 마지막 열까지 진행한다
			printf("%3d ", matrix[matrix_row][matrix_col]); // 행과 열 값을 출력한다
		printf("\n");
	}
	printf("\n"); // 줄바꿈
	/* Check post conditions */
	 if (matrix == NULL) // 주소가 없을경우 
	 {
		printf("Memory Allocation Failed.\n"); // 동적 메모리 할당 실패 문구를 출력한다
		return;
	}


	return;
}


/* free memory allocated by create_matrix() */
int free_matrix(int** matrix, int row, int col) 
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) // row나 col이 0이하이면
	{
		printf("Check the size of row and col!\n"); // 행과 열 확인하라는 문구를 출력한다
		return -1;
	}

	for (int matrix_row = 0; matrix_row < row; matrix_row++) // 첫번째 행부터 마지막 행까지 진행한다
	 {
		free(matrix[matrix_row]); // matrix 공간이 가리키는 공간을 해제한다
	}

	free(matrix); // matrix 공간을 해제한다
	return 1;
}


/* assign random values to the given matrix */
int fill_data(int** matrix, int row, int col)
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) // row나 col이 0이하이면
	 {
		printf("Check the size of row and col!\n"); // 행과 열 확인하라는 문구를 출력한다
		return -1;
	}
    for (int matrix_row = 0; matrix_row < row; matrix_row++) // 첫번째 행부터 마지막 행까지 진행한다
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // 첫번째 열부터 마지막 열까지 진행한다
			matrix[matrix_row][matrix_col] = rand() % 20; // 0과 19 사이의 값을 랜덤으로 지정한다
	/* Check post conditions */
    if (matrix == NULL) // 주소가 없을 경우 
	{
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 문구를 출력한다
		return -1;
	}
	return 1;
}

/* mmatrix_sum = matrix_a + matrix_b */
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col) // 행렬 a와 b의 합
{
    int** matrix_sum = create_matrix(row, col);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) // row나 col이 0이하이면
	{
		printf("Check the size of row and col!\n"); // 행과 열 확인하라는 문구를 출력한다
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) // 첫번째 행부터 마지막 행까지 진행한다
	{
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // 첫번째 열부터 마지막 열까지 진행한다
			matrix_sum[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] + matrix_b[matrix_row][matrix_col];
			// 행과 열끼리 더한다
	}
	/* Check post conditions */
	if (matrix_a == NULL || matrix_b == NULL || matrix_sum == NULL) {
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 문구를 출력한다
		return -1;
	}

	print_matrix(matrix_sum, row, col); // matrix_sum 값을 출력한다
	free_matrix(matrix_sum, row, col); // 재설정 한다
	return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col) // 행렬 a와 b의 차
{
    int** matrix_sub = create_matrix(row, col);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) // row나 col이 0이하이면
	 {
		printf("Check the size of row and col!\n"); // 행과 열 확인하라는 문구를 출력한다
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) // 첫번째 행부터 마지막 행까지 진행한다
	 {
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // 첫번째 열부터 마지막 열까지 진행한다
			matrix_sub[matrix_row][matrix_col] = matrix_a[matrix_row][matrix_col] - matrix_b[matrix_row][matrix_col];
			// 행과 열끼리 뺀다
	}
	/* Check post conditions */
    if (matrix_a == NULL || matrix_b == NULL || matrix_sub == NULL) {
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 문구를 출력한다
		return -1; 
	}
	print_matrix(matrix_sub, row, col); // matrix_sub 값을 출력한다
	free_matrix(matrix_sub, row, col); // 재설정 한다

	return 1;
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int** matrix, int** matrix_t, int row, int col) // 행렬 전치함수
{
	/* Check pre conditions */
	if (row <= 0 || col <= 0) // row나 col이 0이하이면
	{
		printf("Check the size of row and col!\n"); // 행과 열 확인하라는 문구를 출력한다
		return -1;
	}
	for (int matrix_row = 0; matrix_row < row; matrix_row++) // 첫번째 행부터 마지막 행까지 진행한다
	 {
		for (int matrix_col = 0; matrix_col < col; matrix_col++) // 첫번째 열부터 마지막 열까지 진행한다
			matrix_t[matrix_row][matrix_col] = matrix[matrix_col][matrix_row]; // 행열 을 열행으로 
	}
	/* Check post conditions */
    if (matrix == NULL || matrix_t ==NULL) // 
	{
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 문구를 출력한다
		return -1;
	}

	return 1;
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col) // 행렬 a와 b의 곱
{
    int** matrix_axt = create_matrix(row, row);
	/* Check pre conditions */
	if (row <= 0 || col <= 0) // row나 col이 0이하이면
	 {
		printf("Check the size of row and col!\n"); // 행과 열 확인하라는 문구를 출력한다
		return -1;
	}
	for (int matrix_a_row = 0; matrix_a_row < row; matrix_a_row++) // 0부터 행 까지 반복한다
	 {
		for (int matrix_t_row = 0; matrix_t_row < row; matrix_t_row++) // 첫번째 행부터 마지막 행까지 진행한다
		{
			int temp = 0;
			for (int matrix_col = 0; matrix_col < col; matrix_col++) // 첫번째 열부터 마지막 열까지 진행한다
				temp += matrix_a[matrix_a_row][matrix_col] * matrix_t[matrix_col][matrix_t_row]; // 
			matrix_axt[matrix_a_row][matrix_t_row] = temp;
		}
	}
	/* Check post conditions */
    if (matrix_t == NULL || matrix_axt ==NULL) {
		printf("Memory Allocation Failed.\n"); // 메모리 할당 실패 문구를 출력한다
		return -1;
	}
	print_matrix(matrix_axt, row, row); // matrix_axt의 값을 출력한다
	free_matrix(matrix_axt, row, col); // matrix_axt의 값을 넘겨준다
	return 1;
}

