#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

// 用于创建一个唯一的key
#define MSG_FILE "/etc/passwd"

// 消息结构
struct msg_form {
    long mtype; //必须有这个参数
    char mtext[256];
};

int main()
{
    int msqid;
    key_t key;
    struct msg_form msg;
    
    // 获取key值
    if((key = ftok(MSG_FILE,'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }

    // 打印key值
    printf("Message Queue - Server key is: %d.\n", key);

    // 创建消息队列
    if ((msqid = msgget(key, IPC_CREAT|0777)) == -1)
    {
        perror("msgget error");
        exit(1);
    }

    // 打印消息队列ID及进程ID
    printf("My msqid is: %d.\n", msqid);
    printf("My pid is: %d.\n", getpid());

    // 循环读取消息
	msgrcv(msqid, &msg, sizeof(msg.mtext), 888, 0);// 返回类型为888的第一个消息
	printf("Server: receive msg.mtext is: %s.\n", msg.mtext);
	printf("Server: receive msg.mtype is: %ld.\n", msg.mtype);

	/*msg.mtype = 999; // 客户端接收的消息类型
	sprintf(msg.mtext, "hello, I'm server %d", getpid());
	msgsnd(msqid, &msg, sizeof(msg.mtext), 0);*/

	if(msgctl(msqid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        exit(-1);  
    }  
    return 0;
}

/*说明
使用ftok获取键值
在一般的UNIX实现中，是将文件的索引节点号取出，前面加上子序号得到key_t的返回值。
如指定文件的索引节点号为65538，换算成16进制为0x010002，而你指定的ID值为38，换算成16进制为0x26，则最后的key_t返回值为0x26010002。
如果要确保key_t值不变，要么确保ftok的文件不被删除，要么不用ftok，指定一个固定的key_t值
*/