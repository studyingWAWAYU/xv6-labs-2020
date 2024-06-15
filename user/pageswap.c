#include "kernel/types.h"
#include "user/user.h"
#define MAX_REFLEN 100

void PrintRef(int ref[], int refLen){
    printf("访问序列：");
    for(int i=0; i<refLen; i++){
        printf("%d ",ref[i]);
    }
    printf("\n");
}

void PrintRam(int ram[], int phySize){
    printf("内存块：");
    for(int i=0; i<phySize; i++){
        printf("%d ", ram[i]);
    }
    printf("\n");
}

void PrintFinal(int lackNum, int replaceNum, int refLen){
    printf("缺页次数：%d\n", lackNum);
    printf("置换次数：%d\n", replaceNum);
    printf("缺页率：%.2f%%\n", 100.0*lackNum/refLen);
}

void Init(int arr[], int num){
    for(int i=0;i<num;i++){
        arr[i]=-1;
    }
}

void FIFO_select(int ref[], int phySize, int refLen){
    int ram[refLen];
    Init(ram, phySize); //初始化，先将内存块的值都置为-1
    int point = 0;  // 置换指针
    int flag = -1;  //用来标记是否需要置换
    int replaceNum = 0;
    int lackNum = 0;
	
    for(int i=0; i<refLen; i++){
        for(int j=0; j<phySize; j++){
            if(ram[j]==ref[i]){  // 页面命中，不用置换
		printf("visiting%d: ", ref[i]);
		PrintRam(ram, phySize);
		flag = 1;
		break;
            }
            if(ram[j] == -1){  //还有空余位置
                ram[j] = ref[i];
		lackNum++;
		printf("访问 %d: ",ref[i]);
		PrintRam(ram, phySize);
		flag = 1;
		break;
            }
        }
        if(flag == -1){  // 需要页面置换
            ram[point] = ref[i];
            point = (point+1)%phySize;
            replaceNum++;
            lackNum++;
            printf("访问内存%d",ref[i]);
            PrintRam(ram,phySize);
        }
        flag = -1;
    }
    PrintFinal(lackNum, replaceNum, refLen);
}

int main(int argc, char *argv[]) {
    // 检查输入的参数数量是否正确
    if (argc < 3) {
        printf("Usage: pageswap <frame_size> <algorithm> <reference_sequence>\n");
        exit(1);
    }

    // 读取输入参数，用atoi()将输入转换为整数类型
    int phySize = atoi(argv[1]);   // 物理块数量
    int algorithm = atoi(argv[2]); //选择算法，1表示FIFO，2表示LRU
    int refLen = argc-4;        // 引用串的长度

    // 判断输入的参数都要大于0,refLen不能超过最大串长度
    if ( phySize <= 0|| refLen<=0 || refLen > MAX_REFLEN) {
        printf("Invalid input parameters\n");
        exit(1);
    }

    int ref[MAX_REFLEN];
    for(int i=0; i<refLen; i++) {
        ref[i] = atoi(argv[i+4]);
    }
    PrintRef(ref, refLen);

    if (algorithm==1){
	FIFO_select(ref,phySize, refLen);
    } else if(algorithm==2){
	printf("LRU");
    	//LRU_select(copyref,phySize, refLen);
    } else{
    	printf("Unsupported algorithm \n");
    }
    exit(0);
}
