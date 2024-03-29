var RED   = "#FF0000";
var GREEN = "#00FF00";
var BLUE  = "#0000FF";
var GRAY  = "#808080";
var BLACK = "#000000";

var vertexRadius = 10;
var edgeWidth = 10;

function initView () {
	view.currentFrame = frameSlider.value;
	var frameData = obj.frames[view.currentFrame];
	for (var i = 0; i < frameData.graphVertices.length; i++) {
		view.width = Math.max(view.width, frameData.graphVertices[i].x);
		view.height = Math.max(view.height, frameData.graphVertices[i].y);
	}
	if (view.width / canvas.width > view.height / canvas.height) {
		view.height = canvas.height * view.width / canvas.width;
	} else {
		view.width = canvas.width * view.height / canvas.height;
	}
	console.log(view);
}

function scaleToView (obj) {
	return {
		"x": obj.x * (canvas.width / view.width),
		"y": obj.y * (canvas.height / view.height),
	}
}

function drawEdge (e) {
	context.fillStyle = '#f00';
	context.beginPath();
	for (var i = 0; i < points.size(); i++) {

	}
	context.moveTo(0, 0);
	context.lineTo(100,50);
	context.lineTo(50, 100);
	context.lineTo(0, 90);
	context.closePath();
	context.fillStyle = BLUE;
	context.fill();
	context.lineWidth = 2;
	context.strokeStyle = BLACK;
	context.stroke();
}

function drawVertex (v) {
	var loc = scaleToView(v);
	context.beginPath();
	context.arc(loc.x, loc.y, vertexRadius, 0, 2 * Math.PI, false);
	context.closePath();
	context.fillStyle = BLUE;
	context.fill();
	context.lineWidth = 2;
	context.strokeStyle = BLACK;
	context.stroke();
}

function displayFrame (frameNumber) {
	console.log("Displaying frame " + frameNumber);

	context.fillStyle = GREEN;
	context.fillRect(0, 0, canvas.width, canvas.height);

	var frameData = obj.frames[frameNumber];
	for (var i = 0; i < frameData.graphVertices.length; i++) {
		drawVertex(frameData.graphVertices[i]);
	}
}

var canvas = document.getElementById('roadMap');
var	context = canvas.getContext('2d');

canvas.width = screen.width * 0.9;
canvas.height = screen.height * 0.9;

var view = {
	"width": -1,
	"height": -1,
	"currentFrame": -1,
};

/*
 * Frame slider
 */
var frameSlider = document.getElementById("frame-slider");
var frameSliderList = document.getElementById("frame-slider-ticks");
var frameDisplay = document.getElementById("frame-display");

frameSlider.max -= 1;

var tickIntervals = 4;
for (var i = 0; i <= tickIntervals; i++) {
   var option = document.createElement("option");
   option.value = Math.trunc(i * frameSlider.max / tickIntervals);
   frameSliderList.appendChild(option);
}

frameSlider.oninput = function() {
	view.currentFrame = this.value;
	frameDisplay.innerHTML = "Frame: " + view.currentFrame;
	// if (!obj.loaded[this.value]) {
	//     obj.loaded[this.value] = true;
	//     obj.frames[i] = {{{json frames.[REPLACE]}}};
	// }
	displayFrame(view.currentFrame);
}

var obj = {{{json this}}};
/*
// Dynamic loading
var obj = {
	"meta": {{{json meta}}},
	"global": {{{json global}}},
	"frames": [],
	"loaded": [],
};
for (var i = 0; i < obj.global.NUM_TIME_STEP; i++) {
	obj.frames.push({});
	obj.loaded.push(false);
}
*/
initView();
displayFrame(view.currentFrame);
