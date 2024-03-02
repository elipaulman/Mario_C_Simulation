NF>0	{ 
	    split($4, a, ".");
	    goesin = a[1] ".nvs";
	    /* print $1 " comes from " $4 " and goes in " goesin; */
	    printf("%s", $5) > goesin;
	    for(i=6; i <= NF; i++) 
	    { printf(" %s", $i) > goesin;}
	    printf(";\n") > goesin;
	
	}
