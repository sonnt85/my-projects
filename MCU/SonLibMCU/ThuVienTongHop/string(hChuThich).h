/*--------------------------------------------------------------------------
STRING.H

String functions.
Copyright (c) 1988-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __STRING_H__
#define __STRING_H__

#ifndef _SIZE_T
 #define _SIZE_T
 typedef unsigned int size_t;
#endif

#ifndef NULL
 #define NULL ((void *) 0L)
#endif

#pragma SAVE
#pragma REGPARMS
extern char *strcat (char *s1, char *s2); // bo xung chuoi s2 noi vao sau s1
extern char *strncat (char *s1, char *s2, int n); // noi them vao chuoi s1 n ky tu dau tien cua s2

extern char strcmp (char *s1, char *s2); //so sanh 2 chuoi, <0 (s1<s2) =0(s1=s2) >0 (s1>s2) ky tu dau tien nho hon hoac lon hon chuoi kia
extern char strncmp (char *s1, char *s2, int n);////so sanh toi da n ky tu dau cua 2 chuoi hoac khi co ket qua thi thoi

extern char *strcpy (char *s1, char *s2);// cop py chuoi s2 vao vi tri chuoi s1 luon 
extern char *strncpy (char *s1, char *s2, int n);//copy toi da n ky tu cua chuoi s2 vao vi tri chuoi s1 hoac khi gap null truoc thi dung lai
												//s2<lens2 them null
extern int strlen (char *);//tinh do dai chuoi bo ky tu null

extern char *strchr (const char *s, char c);//tim ky tra lai con tro tro toi ky tu dau tien trong s xuat hien c neu k0 tra lai null
extern int strpos (const char *s, char c);//tim ky tu c dau tien xuat hien trong s tra lai index (ko fai con tro )cua no
extern char *strrchr (const char *s, char c);//tim vi tri cuoi cung xuat hien c neu ko co tra lai null
extern int strrpos (const char *s, char c);//tim vi tri cuoi cung xuat hien c trong chuoi s, tra lai index neu thanh cong, -1 neu ko co

extern int strspn (char *s, char *set);//tim index dau tien trong s ma trong set ko co bat cu ky tu nao trong set
extern int strcspn (char *s, char *set);//tim index cuoi cung trong s ma ko giong bat cu ky tu nao trong set 
extern char *strpbrk (char *s, char *set);//tra lai dia chi dau tien trong s ma chua ky tu trong chuoi set neu ko co tra null
extern char *strrpbrk (char *s, char *set);//tra lai dia chi trong s, do la dia chi cuoi cung xuat hien ky tu trong chuoi s(bo null) 
extern char *strstr  (char *s, char *sub);// tra lai con tro tro toi vi tri dau tien ma xuat hien chuoi sub trong chuoi str
extern char *strtok  (char *str, const char *set);

extern char memcmp (void *s1, void *s2, int n);//so sanh n byte trong vung s1 voi s2 <0 s1<s2, >0 s1>s2. =0 s1=s2
extern void *memcpy (void *s1, void *s2, int n);// copy n ky tu tu s2 sang s1(ko co null) tra lai dia chi vung nhan ham nay ko de y tran buff
//ko chac chan la co bi overload ko
extern void *memchr (void *s, char val, int n);//tim ky tu val trong n ky tu dau cua chuois tra ve con tro hoat null(ko co)
extern void *memccpy (void *s1, void *s2, char val, int n);//sao ky tu tu s2 den s1, 
        //dung lai khi val hoac da du n ky tu tra lai con tro tro toi vtri sau cuoi sao chep cua s2 null neu ktu cuoi ko sao dc
extern void *memmove (void *s1, void *s2, int n);//copy n byte tu s2 vao s1(s1 co the < s2 va khi chep bi ghi de  nhung ko bi ghi de 
                      //da loai bo overload truoc khi copy xong,  tra lai dia chi s1,
extern void *memset  (void *s, char val, int n);//gui n ky tu val  vao vung nho s (ko ket thuc bang chuoi
#pragma RESTORE

#endif
