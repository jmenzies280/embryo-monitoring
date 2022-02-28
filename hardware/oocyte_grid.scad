//oocyte chamber
//updated by AM Chagas 20210506 -> larger grid
//designed by AM Chagas 20181001 CC BY 4.0 license
//inspired on the design from J Menzies.

wellx = 2.5;
welly = 2.5;
wellz = 0.5;
interwell = 0.5;
nwellsx = 2;
nwellsy = 2;

platey = wellx*nwellsx*5+30;
platex = welly*nwellsy*1.5+14.5;
platez = 2;

screwD = 3;
screwH = 10;

legL=40;
legD=8;


tol = 0.1;
$fn=20;
module grid(){
    for (x = [0:nwellsx-1]){
        for (y = [0:nwellsy-1]){
            translate([x*(wellx+interwell),y*(welly+interwell),0]){
                cube([wellx,welly,wellz]);
                }//end translate
            }//end for y
    }//end for x
}//end module

module plate(){
difference(){
translate([0,0,-platez/2]){
cube([platex,platey,platez],center=true);
}//end translate
translate([-(nwellsx*(wellx+interwell))/2,-(nwellsy*(welly+interwell))/2,-wellz+0.01]){
grid();
}//end translate
}//end difference

}//end module

module grid_w_holes(){
difference(){
plate();

translate([platex/2-screwD,platey/2-screwD,-screwH/2])
cylinder(d=screwD+2*tol,h=screwH);

translate([-platex/2+screwD,platey/2-screwD,-screwH/2])
cylinder(d=screwD+2*tol,h=screwH);

translate([-platex/2+screwD,-platey/2+screwD,-screwH/2])
cylinder(d=screwD+2*tol,h=screwH);

translate([platex/2-screwD,-platey/2+screwD,-screwH/2])
cylinder(d=screwD+2*tol,h=screwH);

}//end difference


}//end module

module grid_w_legs(){
    plate();
    
    translate([platex/2-legD,platey/2-legD,-legL])
cube([legD,legD,legL]);

translate([-platex/2,platey/2-legD,-legL])
cube([legD,legD,legL]);

translate([-platex/2,-platey/2,-legL])
cube([legD,legD,legL]);

translate([platex/2-legD,-platey/2,-legL])
cube([legD,legD,legL]);
    
    }

//grid_w_legs();
grid_w_holes();
