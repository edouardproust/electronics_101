const int n = 3;		   // number of colors (R, G, B)
int pins[n] = {2, 4, 5};   // GPIO pins for R, G, B respectively
int vals[n] = {255, 0, 0}; // 255 means full brightness, 0 means off
int delay_ms = 10;		   // delay in milliseconds between each step of the fade
int val_increment = 1;	   // how much to increase/decrease the brightness of each color in each step of the fade

/**
 * setup function runs once when the microcontroller is powered on or reset
 */
void setup()
{
	for (int i = 0; i < n; ++i)
	{
		pinMode(pins[i], OUTPUT);
	}
}

// 'from' is the index of the current color that is fading out. 'to' is the index of the next color that is fading in
int from = 0;
int to = 1;

/**
 * loop function runs repeatedly after setup() is called.
 * It runs as fast as possible, so we always use a delay to control the frequency of the loop and avoid overwhelming the microcontroller.
 */
void loop()
{
	// fade from one color to the next
	vals[from] = max(vals[from] -= val_increment, 0);
	vals[to] = min(vals[to] += val_increment, 255);
	analogWrite(pins[from], vals[from]);
	analogWrite(pins[to], vals[to]);

	// if the current color is fully faded out and the next color is fully faded in, move to the next color
	if (vals[from] == 0 && vals[to] == 255)
	{
		from = to;
		to = (to + 1) % n;
	}

	// delay for a short time to control the speed of the fade
	delay(delay_ms);
}
