/**
 * ˵����
 *      ����2���¼����
 *      ��̬�����¼�1�����������¼���־���ֱ�Ϊevent1_flag1��event1_flag2��������'a'������event1_flag1
 *      ������'b'������event1_flag2������ʹ��AND��ֻ�а���'a'��'b'�󣬲Żᴥ���¼��������
 *      ��̬�����¼�2�����������¼���־���ֱ�Ϊevent2_flag1��event2_event2��������'c'������event2_flag1
 *      ������'d'������event2_flag2������ʹ��OR�����ⰴ��'c'����'d'�󣬶��ᴥ���¼��������
 *
 * ע�⣺
 *      Ӣ��Сд���뷨
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-31     zhangran     the first version
 * 2023-04-17     shadow3d     change the output format and file format
 */

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "toolkit.h"

/* �¼�1��� */
struct tk_event event1;
/* �¼�1��־ */
#define event1_flag1 (1 << 1)
#define event1_flag2 (1 << 2)

/* �¼�2��� */
struct tk_event *event2 = NULL;
/* �¼�2��־ */
#define event2_flag1 (1 << 1)
#define event2_flag2 (1 << 2)

int main(int argc, char *argv[])
{
    uint32_t recved;
    /* ��̬�����¼�1 */
    tk_event_init(&event1);
    /* ��̬�����¼�2 */
    event2 = tk_event_create();

    while (1)
    {
        if (_kbhit())
        {
            /* ��ȡ������ */
            int key = _getch();
            /* printf("the key you pressed is %d\n", key); */
            switch (key)
            {
            /* ����'a'*/
            case 97:
                tk_event_send(&event1, event1_flag1);
                printf("Key 'a' pressed send event1_flag1\n");
                break;
            /* ����'b'*/
            case 98:
                tk_event_send(&event1, event1_flag2);
                printf("Key 'b' pressed send event1_flag2\n");
                break;
            /* ����'c'*/
            case 99:
                tk_event_send(event2, event2_flag1);
                printf("Key 'c' pressed send event2_flag1\n");
                break;
            /* ����'d'*/
            case 100:
                tk_event_send(event2, event2_flag2);
                printf("Key 'd' pressed send event2_flag2\n");
                break;
            }
        }

        /* �¼�1ͬʱ���յ��˱�־1�ͱ�־2�������־�������¼�������� */
        if (true == tk_event_recv(&event1,
                                  (event1_flag1 | event1_flag2),
                                  TK_EVENT_OPTION_AND | TK_EVENT_OPTION_CLEAR,
                                  &recved))
        {
            printf("trigger event and clear event\n");
            printf("event1: AND recv event 0x%x\n\n", recved);
        }

        /* �¼�2���յ��˱�־1���־2�������־�������¼�������� */
        if (true == tk_event_recv(event2,
                                  (event2_flag1 | event2_flag2),
                                  TK_EVENT_OPTION_OR | TK_EVENT_OPTION_CLEAR,
                                  &recved))
        {
            printf("trigger event and clear event\n");
            printf("event2: OR recv event 0x%x\n\n", recved);
        }
    }

    return 0;
}
