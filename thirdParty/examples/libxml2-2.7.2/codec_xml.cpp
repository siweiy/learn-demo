#include <string.h>
#include <libxml/parser.h>

/* 对指定编码格式的外部数据，转换成libxml使用UTF-8格式 */
unsigned char * convert(unsigned char *in, char *encoding)
{
    unsigned char *out;
    int ret, size, out_size, temp;
    /* 定义一个编码处理器指针 */
    xmlCharEncodingHandlerPtr handler;

    size = (int)strlen((const char *)in) + 1;        /* 输入数据长度 */
    out_size = size * 2 - 1;                         /* 输出数据长度 */
    out = (unsigned char *)malloc((size_t)out_size); /* 存放输出数据 */

    if (out)
    {
        /* 查找内建的编码处理器 */
        handler = xmlFindCharEncodingHandler(encoding);
        if (!handler)
        {
            free(out);
            out = NULL;
        }
    }
    if (out)
    {
        temp = size - 1;
        /* 对输入数据进行编码转换 */
        ret = handler->input(out, &out_size, in, &temp);
        if (ret || temp - size + 1)
        { /* 转换不成功 */
            if (ret)
            { /* 转换失败 */
                printf("conversion wasn't successful.\n");
            }
            else
            { /* 只转换了一部分数据 */
                printf("conversion wasn't successful. converted: %i octets.\n", temp);
            }
            free(out);
            out = NULL;
        }
        else
        { /* 转换成功 */
            out = (unsigned char *)realloc(out, out_size + 1);
            out[out_size] = 0; /* 输出的末尾加上null终止符 */
        }
    }
    else
    {
        printf("no mem\n");
    }
    return (out);
}

int main(int argc, char **argv)
{
    unsigned char *content, *out;
    xmlDocPtr doc;
    xmlNodePtr rootnode;
    char *encoding = "ISO-8859-1";

    if (argc <= 1)
    {
        printf("Usage: %s content\n", argv[0]);
        return (0);
    }

    content = (unsigned char *)argv[1];
    /* 转换成libxml2使用的UTF-8格式 */
    out = convert(content, encoding);
    doc = xmlNewDoc(BAD_CAST "1.0");
    rootnode = xmlNewDocNode(doc, NULL, (const xmlChar *)"root", out);
    xmlDocSetRootElement(doc, rootnode);
    /* 以ISO-8859-1格式输出文档内容 */
    xmlSaveFormatFileEnc("-", doc, encoding, 1);

    return (0);
}