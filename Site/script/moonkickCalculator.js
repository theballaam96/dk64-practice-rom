function calculate(sY,eY) {
	var preKickFrames = 4;
	var kickInit = [
		140, 130, 126, 119,
		112, 105, 91, 84,
		140, 140, 140, -40, // Last entry is 160 - 200
	]
	var postRoll = [
		195, 190, 200, 210,
		220, 230, 240, 250,
		250, 250, 250, 250,
		250, 250, 250, 250,
		250, 250, 250, 250,
		250, 250, 250, 250,
		250, 230, 210, 190,
		170, 150, 140, 140,
		140, 140, 140, 140,
		140, 140, 140, 140,
		140, 140,
	]
	var aY = -2.5
	var focused_vY = 130;
	var total = (preKickFrames * 140);
	var totalFrames = preKickFrames;
	kickInit.forEach(speed => {
		total += speed;
		totalFrames += 1;
	})
	var dY = 0;
	var cancel_condition = false;
	var diff = eY - sY;
	while (!cancel_condition) {
		total += 200;
		totalFrames += 1;
		dY += (focused_vY / 40);
		focused_vY += aY;
		if (focused_vY < 0) {
			if (dY <= diff) {
				cancel_condition = true;
			}
		}
	}
	console.log("Raw Moonkick: " + (total / totalFrames));
	postRoll.forEach(speed => {
		total += speed;
		totalFrames += 1;
	})
	console.log("Moonkick Roll: " + (total / totalFrames))
}