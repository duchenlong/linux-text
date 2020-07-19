#include <cstdio>
#include <cstdlib>
#include <mysql/mysql.h>
#include <iostream>
#include <string>

using namespace std;

void  Insert(char* buf)
{
    //插入数据
#define INSERT_TAG_INFO "insert into tag_blog values (%d,'%s')"
    sprintf(buf,INSERT_TAG_INFO,3,"java 语言");
}

void Select(char* buf)
{
#define SELECT_TAG_INFO "select * from tag_blog;"
    sprintf(buf,SELECT_TAG_INFO);
}

int main()
{
    //初始化句柄
    MYSQL* mysql_fd = mysql_init(NULL);

    //建立连接
    //参数依次为 数据库操作句柄 ip地址 登录用户名 密码 数据库名 端口号
    // unix_socket --》 置NULL
    // client_flag --》 置0
    if(mysql_real_connect(mysql_fd,"127.0.0.1","root","266448",
                "blog_system",3306,NULL,0) == NULL)
    {
        printf("连接失败，错误信息为：[%s]\n",mysql_error(mysql_fd));
        return 0;
    }
    
    //设置编码格式
    mysql_set_character_set(mysql_fd,"utf8");
   
    char buf[1024] = {'\0'};
    //Insert(buf);
    Select(buf);
    //执行sql语句
    int ret = mysql_query(mysql_fd,buf);
    if(ret < 0)
    {
        printf("连接失败，错误信息为：[%s]\n",mysql_error(mysql_fd));
        return 0;
    }

    //查询时候调用
    //遍历查询结果
    MYSQL_RES* result = mysql_store_result(mysql_fd);
    if(result == NULL)
    {
        printf("查询失败，错误信息为：[%s]\n",mysql_error(mysql_fd));
        return 0;
    }

    //获取行数和列数
    int row = mysql_num_rows(result);
    int col = mysql_num_fields(result);
    printf("row = [%d] col = [%d]\n",row,col);

    //打印结果
    for(int i = 0; i < row; i++)
    {
        MYSQL_ROW r = mysql_fetch_row(result);
        for(int j = 0; j < col; j++)
            printf("%s\t",r[j]);
        printf("\n");
    }

    //释放结果集
    mysql_free_result(result);

    //关闭句柄
    mysql_close(mysql_fd);
    printf("执行成功\n");

    return 0;
}
