NOSYMBOLS, NOPUBLICS 
RAMSIZE(256) 
CODE( 0X0000-0XFFFF ) ;
;NOOVERLAY 
OVERLAY ( 
  *!nhappass,*!inputstttb,*!caidathengio,*!inputonoffbit,*!nhaythietbi,*!inputincdec,*!datsothietbi,*!digi2textbin
 ,ngattime2 ! (?C_C51STARTUP,?PR?MAIN?MAIN,nhappass,datsothietbi,caidattungthietbi,main,inputstttb
 ,caidathengio,inputincdec,inputonoffbit,nhaythietbi,digi2textbin)
 ,setthoigianugetkey  ! (getkeyab)//troham 
 ,settimeugetkey ! (getkeyab)//troham
) 
