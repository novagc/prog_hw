class Point {
	constructor(x, y) {
		this.x = x;
		this.y = y;
	}
}

class Circle {
	constructor(x, y, r) {
		this.x = x;
		this.y = y;
		this.r = r;
		this.d = 2 * r;
	}
}

class Line {
	constructor(firstPoint, secondPoint) {
		this.p1 = firstPoint;
		this.p2 = secondPoint;

		this.k = (this.p2.y - this.p1.y) / (this.p2.x - this.p1.x);
		this.b = (this.p1.x * this.p1.y - this.p1.x * this.p2.y) / (this.p2.x - this.p1.x) + this.p1.y;
	}
}

class Triangle {
	constructor(firstPoint, secondPoint, thirdPoint) {
		this.p1 = firstPoint;
		this.p2 = secondPoint;
		this.p3 = thirdPoint;

		this.l1 = new Line(this.p1, this.p2);
		this.l2 = new Line(this.p2, this.p3);
		this.l3 = new Line(this.p3, this.p1);
	}
}

let dots = [];
let solution;

let sel;
let btn;
let mode = 1;

let circles = [];
let points = [];
let triangles = [];
let lines = [];

let sPoints = [];

function drawField() {
	let w = width / 60;
	let c = color(0, 0, 0, 15);
	strokeWeight(1);
	stroke(0);

	stroke(c);

	for (let y = 0; y < width; y += w) {
		line(0, y, width, y);
	}

	for (let x = 0; x < width; x += w) {
		line(x, 0, x, height);
	}
}

function solutionForThreePoints() {
	if (solution) {
		dots.forEach((v, i) => {
			strokeWeight(2);
			stroke(235, 81, 96, 60);

			line(v.x, v.y, solution.x, solution.y);
			stroke(0);
			strokeWeight(0);
			text(`P${i + 1}`, v.x + 5, v.y + 5);
		});

		strokeWeight(7);
		stroke("black");
		dots.forEach((v, i) => {
			point(v.x, v.y);
		});

		strokeWeight(9);
		stroke("red");
		point(solution.x, solution.y);

		if (solution.ok) {
			strokeWeight(0);
			text(`O`, solution.x + 5, solution.y + 5);
		}
	} else {
		strokeWeight(7);
		stroke("black");
		dots.forEach((v, i) => {
			strokeWeight(7);
			point(v.x, v.y);
			stroke(0);
			strokeWeight(0);
			text(`P${i + 1}`, v.x + 5, v.y + 5);
		});
	}
}

function solutionForFourPoints() {
	noFill();
	stroke("green");
	strokeWeight(1);

	circles.forEach(el => {
		circle(el.x, el.y, el.r * 2);
	});

	stroke("black");
	strokeWeight(2);
	
	triangles.forEach(el => {
		triangle(el.p1.x, el.p1.y, el.p2.x, el.p2.y, el.p3.x, el.p3.y);
	})

	stroke("blue");
	strokeWeight(10);

	points.forEach(el => {
		point(el.x, el.y);
	});

	strokeWeight(3);

	lines.forEach(el => {
		line(el.p1.x, el.p1.y, el.p2.x, el.p2.y);
	});

	stroke("black");
	fill(0);
	dots.forEach((v, i) => {
		strokeWeight(7);
		point(v.x, v.y);
		strokeWeight(0);
		text(`P${i + 1}`, v.x + 5, v.y + 5);
	});

	if(solution) {
		strokeWeight(7);
		stroke("red");

		solution.points.forEach(el => {
			point(el.x, el.y);
		});

		strokeWeight(4);
		stroke('red');

		solution.lines.forEach(el => {
			line(el.p1.x, el.p1.y, el.p2.x, el.p2.y);
		})
	}
}

function setup() {
	createCanvas(windowWidth, windowHeight);
	frameRate(10);
}

function draw() {
	background(255);
	drawField();
	textSize(15);

	button = createButton("Очистить поле");
	button.position(10, 10);
	button.mousePressed(clearField);

	btn = createButton(mode == 1 ? "3 точки" : "4 точки");
	btn.position(130, 10);
	btn.mousePressed(() => {
		mode = -mode;
		clearField();
	});

	switch (mode) {
		case 1:
			solutionForThreePoints();
			break;
		case -1:
			solutionForFourPoints();
			break;
	}
}

function clearField() {
	dots = [];
	solution = null;
	points = [];
	circles = [];
	triangles = [];
	lines = [];
	clear();
}

function mouseClicked() {
	if (mouseX < 200 && mouseY < 75) {
		return;
	}

	switch (mode) {
		case 1:
			if (dots.length >= 3) {
				dots.shift();
			}

			dots.push(new Point(mouseX, mouseY));

			if (dots.length < 3) {
				return;
			}
			solution = SolveForThree(
				Array(3)
					.fill()
					.map((el, i) => dots[i].x),
				Array(3)
					.fill()
					.map((el, i) => dots[i].y)
			);
			break;
		case -1:
			if (dots.length >= 4) {
				clearField();
			}

			dots.push(new Point(mouseX, mouseY));

			if (dots.length < 4) {
				return;
			}

			solution = SolveForFour(dots);
	}
}

function windowResized() {
	resizeCanvas(windowWidth, windowHeight);
}

function SolveForThree(x, y) {
	const lim = Math.PI * 2 / 3;

	let angles = [
		Math.abs(GetAngle({ x: x[0], y: y[0] }, { x: x[1], y: y[1] }, { x: x[2], y: y[2] })),
		Math.abs(GetAngle({ x: x[1], y: y[1] }, { x: x[2], y: y[2] }, { x: x[0], y: y[0] })),
		Math.abs(GetAngle({ x: x[2], y: y[2] }, { x: x[1], y: y[1] }, { x: x[0], y: y[0] })),
	];

	if (angles.filter(x => x >= lim).length > 0) {
		let
			mx = max(angles),
			index = angles.indexOf(mx);
		return { x: x[index], y: y[index] };
	} else {
		let
			r12 = Math.sqrt((x[0] - x[1]) ** 2 + (y[0] - y[1]) ** 2),
			r13 = Math.sqrt((x[0] - x[2]) ** 2 + (y[0] - y[2]) ** 2),
			r23 = Math.sqrt((x[1] - x[2]) ** 2 + (y[1] - y[2]) ** 2),
			s = x[0] * y[1] + x[1] * y[2] + x[2] * y[0] - x[0] * y[2] - x[2] * y[1] - x[1] * y[0],
			k1 = (Math.sqrt(3) / 2) * (r12 ** 2 + r13 ** 2 - r23 ** 2) + Math.abs(s),
			k2 = (Math.sqrt(3) / 2) * (r23 ** 2 + r12 ** 2 - r13 ** 2) + Math.abs(s),
			k3 = (Math.sqrt(3) / 2) * (r13 ** 2 + r23 ** 2 - r12 ** 2) + Math.abs(s),
			d = (1 / Math.sqrt(3)) * (k1 + k2 + k3),
			Px = ((k1 * k2 * k3) / (2 * Math.sqrt(3) * Math.abs(s) * d)) * (x[0] / k1 + x[1] / k2 + x[2] / k3),
			Py = ((k1 * k2 * k3) / (2 * Math.sqrt(3) * Math.abs(s) * d)) * (y[0] / k1 + y[1] / k2 + y[2] / k3);

		return { x: Px, y: Py };
	}
}

function SolveForFour(p) {
	const 
		sqrt3 = Math.sqrt(3),
		lim = Math.PI * 2 / 3;
	let
		left = Array.from(p).sort((a, b) => a.x - b.x),
		lu = (left[0].y < left[1].y ? left[0] : left[1]),
		ld = (left[0].y < left[1].y ? left[1] : left[0]),
		ru = (left[2].y < left[3].y ? left[2] : left[3]),
		rd = (left[2].y < left[3].y ? left[3] : left[2]),
		lip = LinesItersection(new Line(ru, lu), new Line(ld, rd)),
		a1 = GetAngle(lu, ld, ru),
		a2 = GetAngle(ld, lu, rd),
		a3 = GetAngle(rd, ld, ru),
		a4 = GetAngle(ru, lu, rd);
	
	if (a1 > lim || a2 > lim || a3 > lim || a4 > lim) {
		let l = [
			GetLength(lu, ru),
			GetLength(ld, rd),
			GetLength(lu, ld),
			GetLength(ru, rd)
		],

		mx = max(l),
		ind = l.indexOf(mx);

		return {
			points: [],

			lines: [
				new Line(lu, ru),
				new Line(ld, rd),
				new Line(lu, ld),
				new Line(ru, rd)
			]
			.filter((el, i) => i != ind)
		}
	}

	if (lip) {
		if (lip.x >= min([lu.x, ld.x, ru.x, rd.x]) && lip.x <= max([lu.x, ld.x, ru.x, rd.x])) {
			let temp = ru

			ru = rd
			rd = temp
		}
	}

	let
		l1 = GetLength(lu, ru),
		l2 = GetLength(ld, rd),
		l3 = GetLength(lu, ld),
		l4 = GetLength(ru, rd),
		g  = true,
		gl1 = l1,
		gl2 = l2,
		p1 = lu,
		p4 = rd,
		p2,
		p3,
		gl;

	if (l1 + l2 < l3 + l4) {
		p2 = ru;
		p3 = ld;
	}
	else {
		p2 = ld;
		p3 = ru;

		gl1 = l3;
		gl2 = l4;

		g = false;
	}
	circles = [
		{
			x: p1.x,
			y: p1.y,
			r: gl1,
		},
		{
			x: p2.x,
			y: p2.y,
			r: gl1,
		},
		{
			x: p3.x,
			y: p3.y,
			r: gl2,
		},
		{
			x: p4.x,
			y: p4.y,
			r: gl2,
		}
	]
	let 
		tp = CirclesItersection(new Circle(p1.x, p1.y, gl1), new Circle(p2.x,p2.y, gl1)).concat(CirclesItersection(new Circle(p3.x, p3.y, gl2), new Circle(p4.x, p4.y, gl2))),
		gp1,
		gp2;
	
	if (g) {
		gp1 = tp[0].y < tp[1].y ? tp[0] : tp[1];
		gp2 = tp[2].y > tp[3].y ? tp[2] : tp[3];
	} else {
		gp1 = tp[0].x < tp[1].x ? tp[0] : tp[1];
		gp2 = tp[2].x > tp[3].x ? tp[2] : tp[3];
	}

	console.log([p1, p2, p3, p4, tp, gp1, gp2]);

	gl = new Line(gp1, gp2)

	points.push(gp1);
	points.push(gp2);
	lines.push(gl);

	triangles.push(new Triangle(p1, p2, gp1));
	triangles.push(new Triangle(p3, p4, gp2));
	
	l1 = new Line(gp1, new Point((p1.x + p2.x) / 2, (p1.y + p2.y) / 2));
	l2 = new Line(p1, new Point((gp1.x + p2.x) / 2, (gp1.y + p2.y) / 2));
	l3 = new Line(gp2, new Point((p3.x + p4.x) / 2, (p3.y + p4.y) / 2));
	l4 = new Line(p3, new Point((gp2.x + p4.x) / 2, (gp2.y + p4.y) / 2));

	lip = [LinesItersection(l1, l2), LinesItersection(l3, l4)];
	
	let 
		c1 = new Circle(lip[0].x, lip[0].y, gl1/sqrt3),
		c2 = new Circle(lip[1].x, lip[1].y, gl2/sqrt3);

	circles.push(c1);
	circles.push(c2);

	tp = LineCircleItersection(c1, gl).concat(LineCircleItersection(c2, gl));

	if (g) {
		gp1 = tp[0].y > tp[1].y ? tp[0] : tp[1];
		gp2 = tp[2].y < tp[3].y ? tp[2] : tp[3];
	} else {
		gp1 = tp[0].x > tp[1].x ? tp[0] : tp[1];
		gp2 = tp[2].x < tp[3].x ? tp[2] : tp[3];
	}

	return {
		points: [
			gp1, 
			gp2
		],
		lines: [
			new Line(gp1,gp2),
			new Line(p1, gp1), 
			new Line(p2, gp1),
			new Line(p3, gp2),
			new Line(p4, gp2)
		]
	};
}

function GetAngle(mainPoint, firstPoint, secondPoint) {
	let
		x1 = firstPoint.x - mainPoint.x,
		x2 = secondPoint.x - mainPoint.x,
		y1 = firstPoint.y - mainPoint.y,
		y2 = secondPoint.y - mainPoint.y,
		d1 = Math.sqrt(x1 ** 2 + y1 ** 2),
		d2 = Math.sqrt(x2 ** 2 + y2 ** 2);

	return Math.acos((x1 * x2 + y1 * y2) / (d1 * d2));
}

function LineCircleItersection(circle, line) {
	let
		a = 1 + line.k ** 2,
		b = -2 * circle.x + 2 * line.k * line.b - 2 * line.k * circle.y,
		c = -(circle.r ** 2) + (line.b - circle.y) ** 2 + circle.x ** 2,
		d = b ** 2 - 4 * a * c;

	if (d < 0) {
		return [];
	}
	let
		x1 = (-b - Math.sqrt(d)) / (2 * a),
		x2 = (-b + Math.sqrt(d)) / (2 * a);

	return [
		new Point(x1, line.k * x1 + line.b),
		new Point(x2, line.k * x2 + line.b),
	]
}

function CirclesItersection(firstCircle, secondCircle) {
	let
		d = GetLength(firstCircle, secondCircle),
		a = (firstCircle.r ** 2 - secondCircle.r ** 2 + d ** 2) / (2 * d),
		h = Math.sqrt(firstCircle.r ** 2 - a ** 2),
		x3 = firstCircle.x + (a / d) * (secondCircle.x - firstCircle.x),
		y3 = firstCircle.y + (a / d) * (secondCircle.y - firstCircle.y),
		kx = (h / d) * (secondCircle.x - firstCircle.x),
		ky = (h / d) * (secondCircle.y - firstCircle.y);

	return [
		new Point(+(x3 - ky).toFixed(10), +(y3 + kx).toFixed(10)),
		new Point(+(x3 + ky).toFixed(10), +(y3 - kx).toFixed(10)),
	];
}

function LinesItersection(firstLine, secondLine) {
	if (firstLine.k == secondLine.k)
		return undefined;

	let a = (secondLine.b - firstLine.b) / (firstLine.k - secondLine.k);

	return new Point(a, firstLine.k * a + firstLine.b);
}

function GetLength(p1, p2) {
	return Math.sqrt((p2.x - p1.x) ** 2 + (p2.y - p1.y) ** 2);
}