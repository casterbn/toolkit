/**
 * ˵����
 *      ����4����ʱ��
 *      ��ʱ��1��2Ϊ��̬������������һ����ʱ�ص�������
 *      ��ʱ��3��4Ϊ��̬�������������Լ��ĳ�ʱ�ص�����
 *      ����20 tick ����timer2��ɾ��timer4��ֻ��timer1��3����
 *      Ϊ����ʾ���㣬main������ѭ��1s tick��1����ѭ������tk_timer_loop_handler������
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-01-29     zhangran     the first version
 * 2023-04-17     shadow3d     change comment format
 */

#include <windows.h>
#include <stdio.h>
#include "toolkit.h"

uint32_t tick = 0;
/* �����ȡϵͳtick�ص����� */
uint32_t get_sys_tick(void)
{
    return tick;
}

/* ��ʱ����� */
struct tk_timer timer1;
struct tk_timer timer2;
struct tk_timer *timer3 = NULL;
struct tk_timer *timer4 = NULL;

/* ��ʱ��1��2���õĳ�ʱ�ص����� */
void timer_timeout_callback(struct tk_timer *timer)
{
    if (timer == &timer1)
        printf("timeout_callback: timer1 timeout:%ld\n", get_sys_tick());
    else if (timer == &timer2)
        printf("timeout_callback: timer2 timeout:%ld\n", get_sys_tick());
}

/* ��ʱ��3��ʱ�ص����� */
void timer3_timeout_callback(struct tk_timer *timer)
{
    printf("timeout_callback: timer3 timeout:%ld\n", get_sys_tick());
}

/* ��ʱ��4��ʱ�ص����� */
void timer4_timeout_callback(struct tk_timer *timer)
{
    printf("timeout_callback: timer4 timeout:%ld\n", get_sys_tick());
}

int main(int argc, char *argv[])
{
    /* ��ʼ�������ʱ�����ܣ�������tick��ȡ�ص�����*/
    tk_timer_func_init(get_sys_tick);

    /* ��̬������ʱ��1��2 */
    tk_timer_init(&timer1, timer_timeout_callback);
    tk_timer_init(&timer2, timer_timeout_callback);

    /* ��̬������ʱ��3 */
    timer3 = tk_timer_create(timer3_timeout_callback);
    if (timer3 == NULL)
    {
        printf("timer3 create error!\n");
        return 0;
    }

    /* ��̬������ʱ��4 */
    timer4 = tk_timer_create(timer4_timeout_callback);
    if (timer4 == NULL)
    {
        printf("timer4 create error!\n");
        return 0;
    }

    /* ������ʱ��1��ѭ��ģʽ��5tickʱ�� */
    tk_timer_start(&timer1, TIMER_MODE_LOOP, 5);
    /* ������ʱ��2��ѭ��ģʽ��3tickʱ�� */
    tk_timer_start(&timer2, TIMER_MODE_LOOP, 3);

    /* ������ʱ��3��ѭ��ģʽ��5tickʱ�� */
    tk_timer_start(timer3, TIMER_MODE_LOOP, 5);
    /* ������ʱ��4��ѭ��ģʽ��3tickʱ�� */
    tk_timer_start(timer4, TIMER_MODE_LOOP, 3);
    while (1)
    {
        /* ��ʱ��������� */
        tk_timer_loop_handler();
        printf("tick:%ld\n", get_sys_tick());

        /* ����20 tick ����timer2��ɾ��timer4 */
        if (tick == 20)
        {
            tk_timer_detach(&timer2);
            tk_timer_delete(timer4);
            printf("timer2 detach timer4 delete.\n");
        }
        tick++;
        Sleep(1000);
    }

    return 0;
}

#if 0

/* ��Ƭ�� α���� */

#include <stdio.h>
#include "toolkit.h"

struct tk_timer timer1;
struct tk_timer timer2;

/* stm32 �δ�ʱ���ж�,����1ms�ж�һ�� */
void SysTick_Handler(void)
{
	tick++;
}

/* �����ȡϵͳtick�ص����� */
uint32_t get_sys_tick(void)
{
	return tick;
}


/* ��ʱ��1��ʱ�ص����� */
void timer1_timeout_cb(struct tk_timer *timer)
{

	printf("timeout_callback: timer1 timeout.\n");
}

/* ��ʱ��2��ʱ�ص����� */
void timer2_timeout_cb(struct tk_timer *timer)
{
	printf("timeout_callback: timer2 timeout.\n");
}


int main(void)
{
	bsp_init();
	/* ��ʼ�������ʱ�����ܣ�������tick��ȡ�ص�����*/
	tk_timer_func_init(get_sys_tick);
	/* ��̬������ʱ��1��2 */
	tk_timer_init(&timer1, (timeout_callback*)timer1_timeout_cb);
	tk_timer_init(&timer2, (timeout_callback*)timer2_timeout_cb);

	/* ������ʱ��1��ѭ��ģʽ��5��ʱ�� */
	tk_timer_start(&timer1, TIMER_MODE_LOOP, 5000);
	/* ������ʱ��2��ѭ��ģʽ��3��ʱ�� */
	tk_timer_start(&timer2, TIMER_MODE_LOOP, 1000);
	while (1)
	{
		tk_timer_loop_handler();
	}
}

#endif
