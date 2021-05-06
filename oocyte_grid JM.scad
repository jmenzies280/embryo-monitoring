//oocyte chamber
//updated by AM Chagas 20210506 -> larger grid
//designed by AM Chagas 20181001 CC BY 4.0 license
//inspired on the design from J Menzies.

wellx = 3;
welly = 3;
wellz = 0.8;
interwell = 0.24;
nwellsx = 3;
nwellsy = 4;

platey = wellx*nwellsx*5;
platex = welly*nwellsy*1.5    ;
platez = 2;


module grid(){
    for (x = [0:nwellsx-1]){
        for (y = [0:nwellsy-1]){
            translate([x*(wellx+interwell),y*(welly+interwell),0]){
                cube([wellx,welly,wellz]);
                }//end translate
            }//end for y
    }//end for x
}//end module

difference(){
translate([0,0,-platez/2]){
cube([platex,platey,platez],center=true);
}//end translate
translate([-(nwellsx*(wellx+interwell))/2,-(nwellsy*(welly+interwell))/2,-wellz+0.01]){
grid();
}//end translate
}//end difference
