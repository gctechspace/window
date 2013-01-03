difference () {
	union() {
		cube (size = [31, 23, 6], center=false);
		translate([-5, -5, 6])
		cube (size = [41, 33, 1], center=false);
	}
	translate([0.5, 0.5, 0.5])
	cube (size = [30, 22, 8], center=false);
	translate([2, 2, 0])
	cube (size = [27, 19, 1], center=false);
	translate([-2, -2, 6])
	cylinder (h = 1, r=1.5, center = false, $fn=100);
	translate([-2, 25, 6])
	cylinder (h = 1, r=1.5, center = false, $fn=100);
	translate([33, -2, 6])
	cylinder (h = 1, r=1.5, center = false, $fn=100);
	translate([33, 25, 6])
	cylinder (h = 1, r=1.5, center = false, $fn=100);
}

