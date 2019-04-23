$(function() {
	// w , h are canvas baseX and baseY are anchor point
	var w = 600,
		h = 600,
		baseX = w/2,
		baseY = h/2,
		jointW = 100,
		jointH = 10,
		offsetLeft,
		offsetTop;
	
	// make canvas	
	var paper = Raphael("main", w, h);
	
	

	//array of paper rectangle's 
	var joints = [];
	var selected = null;
	
	var mousedown = false;
	
	

	function initJoints(n) {
		if(joints.length > 0) {
			for(var i=0; i<joints.length; i++) {
				joints[i].remove();
			}
			joints=[];
			selected = null;
		}
		
		
		for(var i=0; i<n; i++) {
			var j = paper.rect(
				baseX,
				baseY - jointH/2,
				jointW,
				jointH,
				jointH/2
			);
			
			j.attr({
				fill: "#9cf",
				stroke: "#38f",
				cursor: "pointer"
			});

			j.data("index", i);
			j.data("rotation", 0);
	
			
			joints.push(j);
		}
		
		updatePosesForward();
	}
	// Two joints
	initJoints(2);
	
	/* Forward kinematics
	=========================================================================*/
	
	function updatePosesForward() {
		var totalRotation = 0;
		
		for(var i=0; i<joints.length; i++) {
			var joint = joints[i];
			
			if(i>0) {
				var prevX = joints[i-1].attr("x"),
					prevY = joints[i-1].attr("y");
			} else {
				var prevX = baseX - jointW,
					prevY = baseY;
			}
			
			prevX += jointW * Math.cos(totalRotation);
			prevY += jointW * Math.sin(totalRotation);
			
			joint.transform("");
			joint.attr({
				x: prevX,
				y: prevY
			});
			
			//Rotation at this joint affect all following joints
			totalRotation += joints[i].data("rotation") * Math.PI/180;
			
			joint.rotate(totalRotation * 180/Math.PI, prevX, prevY + jointH/2);
		}
	}




	function rotateAngle(segnum,r) {
		var el = joints[segnum];
		var rotation = parseFloat(el.data("rotation"));

		var x = el.attr("x");
		var y = el.attr("y");

		el.rotate(r, x, y + jointH/2);
		el.data("rotation", rotation + r);

		updatePosesForward();
	}

	var shoulderAngleprev = 0;
	var forearmAngleprev = 0;  

	document.getElementById("submit").onclick = function(){
		var shoulderAngle = +document.getElementById("shoulderAngle").value;
		var forearmAngle = +document.getElementById("forearmAngle").value;

		//Display current values of angles
		// need to reset after 360
		document.getElementById("shoulderAngleout").innerText = shoulderAngle + shoulderAngleprev;
		document.getElementById("forearmAngleout").innerText = forearmAngle + forearmAngleprev;

		shoulderAngleprev = shoulderAngle + shoulderAngleprev
		forearmAngleprev = forearmAngle + forearmAngleprev

		rotateAngle(0,shoulderAngle);
		rotateAngle(1,forearmAngle);
	}
	paper.circle(baseX,baseY+5,jointH).attr({fill: "#9cf",	stroke: "#38f"});
});
