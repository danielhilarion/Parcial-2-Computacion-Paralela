#!/usr/bin/perl

$repeticiones = 30;
@ejecutables = ("matrices");
@matrizSize = ("100","200","400","800","1000", "1200", "2000");
#"100","200","400","800","1000", "1200", "2000", "4000"
@numThreads = ("1","2", "4","8");
$path = "/home/danielhilarion/Computacion/Vacaciones/Matrices4/";

foreach $exe (@ejecutables){
    foreach $hilo (@numThreads){
        foreach $size (@matrizSize){
            $fichero = "$path"."Soluciones/"."$exe"."-size"."$size"."-numThreads"."$hilo";
            print("$fichero \n");
            for($i=0; $i<$repeticiones; $i++){
                #print("$path$exe $size \n");
                system("$path$exe $size $hilo >> $fichero");
            }
        }  
    }
}
exit(1);