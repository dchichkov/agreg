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
;��⠭����� ��ࠡ��稪 ���뢠���
;�室: ax=N ���뢠���
;      dx- ᬥ饭�� ������
;      di 㪠�뢠�� �� dd, � ���஬ �㤥� �࠭����� ���� �����
        push    es
        push    ds
        push    SI
        push    BX
        xor     ah,ah
        shl     ax,1
        shl     ax,1
        mov     si,ax
        xor     ax,ax
        mov     ds,ax        ; ds:[si] =㪠��⥫� �� �����
        les     bx,dword ptr ds:[si]  ;���� �����
        mov     word ptr cs:[di],bx         ;���� �����
        mov     word ptr cs:[di+2],es       ;���� �����
        pushf
        cli
        mov     word ptr ds:[si],dx         ;��⠭���� ������ �����
        mov     word ptr ds:[si+2],cs
        popf
        pop     BX
        pop     SI
        pop     ds
        pop     es
        retf
Sethandler_ndos endp

Reseth_ndos proc far
;����⠭����� ���� ��ࠡ��稪
;  cs:[di] 㪠�뢠�� �� dd, � ���஬ �࠭����� ���� �����
;  al = ����� ���뢠���
        push    ds
        push    es
        push    si
        xor     ah,ah
        shl     ax,1
        shl     ax,1
        mov     si,ax
        xor     ax,ax
        mov     ds,ax        ; ds:[si] =㪠��⥫� �� �����
        les     ax,cs:[di]   ;���� �����
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
_MIX_ON:        ;��९ணࠬ����� ⠩��� � ᠦ��� �� ����� ⠩���
                ;����� ���
                push    DI
                push    CX
                push    DX
                push    AX
                pushf
                push    DS
                mov     ax,word ptr ds:_SEG_DRB
                mov     word ptr cs:SegDRB,ax ;ᥣ����� ���� ����
                mov     ax,word ptr ds:_OFF_DRB
                mov     word ptr cs:OffDRB,ax ;ᬥ饭�� ���� 
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
                mov     DI,offset vekt8h ;dd -��� �࠭���� ��ண�
                mov     DX,offset mixer          ;ᬥ饭�� ������
                and     byte ptr cs:DBCCOP,0f8h
                cli
              ;  push    CS
                call    far ptr Sethandler_ndos
                pop     DS
                mov     AL,036h
                out     043h,AL
                mov     AX,_KD        ;???????������ ���� � ds ��� es
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
LAC:            or      byte ptr cs:FL_IN,1 ;䫠� -����� ���
                inc     word ptr cs:FTC   ;���稪 ������� ⨪��
                mov     ax,word ptr cs:TAsys
                cmp     word ptr cs:FTC,ax ;��� ��� ⨪�?
                jne     LCD                          ;���
                pushf
                call    dword ptr cs:[vekt8h]
                mov     word ptr cs:FTC,0 ;���稪 ����� ⨪��
                push    bx
                push    es
                push    ax
                mov     ax,cs:SegDRB
                mov     es,ax
                mov     ax,cs:OffDRB
                mov     bx,ax
                mov     al,byte ptr es:[bx]       ;����� ᭠�㦨 DBCCOP
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
                mov     AL,cs:DBCCOP         ;����� ॣ �ࠢ� ��蠫��
                out     DX,AL
                and     al,7
                inc     AL
                cmp     AL,6                         ;�����祭 ����� ��蠫��?
                jb      LE1                          ;-���
                mov     AL,0
LE1:            and     byte ptr cs:DBCCOP,0f8h
                or      cs:DBCCOP,AL         ;����� ॣ �ࠢ� ��蠫��
                and     byte ptr cs:FL_IN,0FEh       ;���⨫� 䫠� -����� ��
LEB:            pop     AX
                pop     DX
                iret
FL_IN           db      0
DBCCOP            db      0
FTC             dw      0
vekt8h          dd      ?                   ;old sist vek
TAsys           dw      6                  ;�१ ᪮�쪮 ⨪�� ����
                                           ;��� ��⥬���� ⨪�
SegDRB           dw      0                  ;ᥣ����� ���� ����
OffDRB           dw      0                  

AGRTIM_TEXT     ends
end
