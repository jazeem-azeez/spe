unit set64kcl;

interface
uses graph;

procedure init64k(gm : integer);
procedure setrgbcolor(r,g,b : byte);
procedure close64k;




implementation

procedure init64k(gm : integer);
var
gd : integer;
begin
if gm > 0
then inc(gm,2);
gd := InstallUserDriver('svga64k',@gm);
initgraph(gd,gm,'');
end;

procedure setrgbcolor(r,g,b : byte);
begin
if g = 31
then g := 63
else g := g * 2;
setrgbpalette(1024,r,g,b);
setrgbpalette(1025,r,g,b);
end;

procedure close64k;
begin
closegraph;
end;


end.
