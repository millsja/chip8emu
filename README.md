# chip8emu

## Instruction set checklist
    Opcode	C Pseudo
[ ] 0NNN    not implemented	
[ ] 000E	disp_clear()
[ ] 00EE	return;
[ ] 1NNN	goto NNN;
[ ] 2NNN	*(0xNNN)()
[ ] 3XNN	if(Vx==NN)
[ ] 4XNN	if(Vx!=NN)
[ ] 5XY0	if(Vx==Vy)
[ ] 6XNN	Vx = NN
[ ] 7XNN	Vx += NN
[ ] 8XY0	Vx=Vy
[ ] 8XY1	Vx=Vx|Vy
[ ] 8XY2	Vx=Vx&Vy
[ ] 8XY3	Vx=Vx^Vy
[ ] 8XY4	Vx += Vy
[ ] 8XY5	Vx -= Vy
[ ] 8XY6	Vx>>=1
[ ] 8XY7	Vx=Vy-Vx
[ ] 8XYE	Vx<<=1
[ ] 9XY0	if(Vx!=Vy)
[ ] ANNN	I = NNN
[ ] BNNN	PC=V0+NNN
[ ] CXNN	Vx=rand()&NN
[ ] DXYN	draw(Vx,Vy,N)
[ ] EX9E	if(key()==Vx)
[ ] EXA1	if(key()!=Vx)
[ ] FX07	Vx = get_delay()
[ ] FX0A	Vx = get_key()
[ ] FX15	delay_timer(Vx)
[ ] FX18	sound_timer(Vx)
[ ] FX1E	I +=Vx
[ ] FX29	I=sprite_addr[Vx]
[ ] FX33	"set_BCD(Vx); *(I+0)=BCD(3); *(I+1)=BCD(2); *(I+2)=BCD(1);"
[ ] FX55	reg_dump(Vx,&I)
[ ] FX65	reg_load(Vx,&I)
