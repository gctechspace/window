difference () {
	union() {
		translate([-5,-5, 0])
		cube (size = [41, 33, 1], center=false);
		translate([0, 0, 1])
		cube (size = [31, 23, 6], center=false);


	}
	translate([0.5, 0.5, 0])
	cube (size = [30, 22, 5.5], center=false);
	translate([2, 2, 0])
	cube (size = [27, 19, 8], center=false);
	hole(-2, -2);
	hole(-2, 25);
	hole(33, -2);
	hole(33, 25);
}

module hole(x,y) {
	translate([x,y, 0])
	cylinder (h = 1, r=1.5, center = false, $fn=100);
}

