AGRTIM_TEXT     segment byte public 'CODE'
DGROUP  group   _BSS,_DATA
        assume  cs:AGRTIM_TEXT,ds:DGROUP
        extrn   _KD
        extrn   _SEG_DRB,_OFF_DRB
        public  _MIX_OFF,_MIX_ON
AGRTIM_TEXT     ends
_DATA   segment word public 'DATA'
_DATA   ends
_BSS    segment word public 'BSS'
_BSS    ends

AGRTIM_TEXT     segment byte public 'CODE'
Sethandler_ndos proc far
;установить обработчик прерывания
;Вход: ax=N прерывания
;      dx- смещение нового
;      di указывает на dd, в котором будет храниться старый вектор
        push    es
        push    ds
        push    SI
        push    BX
        xor     ah,ah
        shl     ax,1
        shl     ax,1
        mov     si,ax
        xor     ax,ax
        mov     ds,ax        ; ds:[si] =указатель на вектор
        les     bx,dword ptr ds:[si]  ;старый вектор
        mov     word ptr cs:[di],bx         ;старый вектор
        mov     word ptr cs:[di+2],es       ;старый вектор
        pushf
        cli
        mov     word ptr ds:[si],dx         ;установка нового вектора
        mov     word ptr ds:[si+2],cs
        popf
        pop     BX
        pop     SI
        pop     ds
        pop     es
        retf
Sethandler_ndos endp

Reseth_ndos proc far
;восстановить старый обработчик
;  cs:[di] указывает на dd, в котором храниться старый вектор
;  al = номер прерывания
        push    ds
        push    es
        push    si
        xor     ah,ah
        shl     ax,1
        shl     ax,1
        mov     si,ax
        xor     ax,ax
        mov     ds,ax        ; ds:[si] =указатель на вектор
        les     ax,cs:[di]   ;старый вектор
        pushf
        cli
        mov     word ptr ds:[si],ax
        mov     word ptr ds:[si+2],es
        popf
        pop     si
        pop     es
        pop     ds
        retf
Reseth_ndos endp
_MIX_ON:        ;перепрограммирует таймер и сажает на вектор таймера
                ;некую проц
                push    DI
                push    CX
                push    DX
                push    AX
                pushf
                push    DS
                mov     ax,word ptr ds:_SEG_DRB
                mov     word ptr cs:SegDRB,ax ;сегментный адрес буфера
                mov     ax,word ptr ds:_OFF_DRB
                mov     word ptr cs:OffDRB,ax ;смещение буфера 
                mov     CX,word ptr ds:_KD
                push    CS
                pop     DS
                cmp     CX,0
                jne     _MIX_ON_10
                mov     word ptr cs:TAsys,6
                jmp     _MIX_ON_20
_MIX_ON_10:
                xor     DX,DX
                mov     AX,0ffffh
                div     CX
                mov     word ptr cs:TAsys,AX
_MIX_ON_20:
                mov     AX,8
                mov     DI,offset vekt8h ;dd -для хранения старого
                mov     DX,offset mixer          ;смещение нового
                and     byte ptr cs:DBCCOP,0f8h
                cli
              ;  push    CS
                call    far ptr Sethandler_ndos
                pop     DS
                mov     AL,036h
                out     043h,AL
                mov     AX,_KD        ;???????должен быть в ds или es
                out     040h,AL
                xchg    AL,AH
                out     040h,AL
                popf
                pop     AX
                pop     DX
                pop     CX
                pop     DI
                retf
_MIX_OFF:       push    DI
                push    AX
                push    DX
                pushf
                cli
                or     byte ptr cs:DBCCOP,7    ;?byte!!
                mov     al,byte ptr cs:DBCCOP
                mov     DX,0131h
                out     DX,AL
                mov     AL,036h
                out     043h,AL
                mov     AL,0FFh
                out     040h,AL
                out     040h,AL
                mov     AL,8
                mov     DI,offset vekt8h
              ;  push    CS
                call    far ptr Reseth_ndos
                popf
                pop     DX
                pop     AX
                pop     DI
                retf
mixer:
                push    DX
                push    AX
                test    byte ptr cs:FL_IN,1    ;byte?!!
                je      LAC
                mov     AL,020h
                out     020h,AL
                jmp short       LEB
                nop
LAC:            or      byte ptr cs:FL_IN,1 ;флаг -внутри прер
                inc     word ptr cs:FTC   ;счетчик быстрых тиков
                mov     ax,word ptr cs:TAsys
                cmp     word ptr cs:FTC,ax ;пора сист тику?
                jne     LCD                          ;нет
                pushf
                call    dword ptr cs:[vekt8h]
                mov     word ptr cs:FTC,0 ;счетчик быстр тиков
                push    bx
                push    es
                push    ax
                mov     ax,cs:SegDRB
                mov     es,ax
                mov     ax,cs:OffDRB
                mov     bx,ax
                mov     al,byte ptr es:[bx]       ;считать снаружи DBCCOP
         ;       mov     al,040h
                and     al,0f8h
                and     byte ptr cs:DBCCOP,7
                or      byte ptr cs:DBCCOP,al
                pop     ax
                pop     es
                pop     bx
;*************************************
                jmp     short       LD1
LCD:            mov     AL,020h
                out     020h,AL
LD1:            mov     DX,0131h
                mov     AL,cs:DBCCOP         ;копия рег управл мешалки
                out     DX,AL
                and     al,7
                inc     AL
                cmp     AL,6                         ;закончен оборот мешалки?
                jb      LE1                          ;-нет
                mov     AL,0
LE1:            and     byte ptr cs:DBCCOP,0f8h
                or      cs:DBCCOP,AL         ;копия рег управл мешалки
                and     byte ptr cs:FL_IN,0FEh       ;очичтили флаг -внутри пр
LEB:            pop     AX
                pop     DX
                iret
FL_IN           db      0
DBCCOP            db      0
FTC             dw      0
vekt8h          dd      ?                   ;old sist vek
TAsys           dw      6                  ;через сколько тиков наших
                                           ;пора системному тику
SegDRB           dw      0                  ;сегментный адрес буфера
OffDRB           dw      0                  

AGRTIM_TEXT     ends
end
