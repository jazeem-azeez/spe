int huge DetectVGA256()
{
  return 2; /* 640 x 480 x 256 Mode*/
}

void Graphinit(void)
{
  int Gd = DETECT, Gm;
  installuserdriver("SVGA256.BGI", DetectVGA256);
  initgraph(&Gd, &Gm, "");

}
