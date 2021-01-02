# chip8emu

Simple C implementation of the [Chip-8 interpreter](https://en.wikipedia.org/wiki/CHIP-8) as used on the 1977 COSMAC VIP. This project is built using C11 with the SDL2 libraries for video, window management.

    ## Instruction set checklist (op code, c pseudo*)
    [ ] 0NNN  ----  not implemented	
    [x] 000E  ----  disp_clear()
    [x] 00EE  ----  return;
    [x] 1NNN  ----  goto NNN;
    [x] 2NNN  ----  *(0xNNN)()
    [x] 3XNN  ----  if(Vx==NN)
    [x] 4XNN  ----  if(Vx!=NN)
    [x] 5XY0  ----  if(Vx==Vy)
    [ ] 6XNN  ----  Vx = NN
    [ ] 7XNN  ----  Vx += NN
    [ ] 8XY0  ----  Vx=Vy
    [ ] 8XY1  ----  Vx=Vx|Vy
    [ ] 8XY2  ----  Vx=Vx&Vy
    [ ] 8XY3  ----  Vx=Vx^Vy
    [ ] 8XY4  ----  Vx += Vy
    [ ] 8XY5  ----  Vx -= Vy
    [ ] 8XY6  ----  Vx>>=1
    [ ] 8XY7  ----  Vx=Vy-Vx
    [ ] 8XYE  ----  Vx<<=1
    [x] 9XY0  ----  if(Vx!=Vy)
    [ ] ANNN  ----  I = NNN
    [ ] BNNN  ----  PC=V0+NNN
    [ ] CXNN  ----  Vx=rand()&NN
    [ ] DXYN  ----  draw(Vx,Vy,N)
    [ ] EX9E  ----  if(key()==Vx)
    [ ] EXA1  ----  if(key()!=Vx)
    [ ] FX07  ----  Vx = get_delay()
    [ ] FX0A  ----  Vx = get_key()
    [ ] FX15  ----  delay_timer(Vx)
    [ ] FX18  ----  sound_timer(Vx)
    [ ] FX1E  ----  I +=Vx
    [ ] FX29  ----  I=sprite_addr[Vx]
    [ ] FX33  ----  "set_BCD(Vx); *(I+0)=BCD(3); *(I+1)=BCD(2); *(I+2)=BCD(1);"
    [ ] FX55  ----  reg_dump(Vx,&I)
    [ ] FX65  ----  reg_load(Vx,&I)

\* c pseudo descriptions from [from Wikipedia](https://en.wikipedia.org/wiki/CHIP-8#Opcode_table)
