// define pins
const int n = 3;
int pins[n] = {2, 4, 5};   // R, G, B
int vals[n] = {255, 0, 0}; // R, G, B
int delay_ms = 10;
int val_increment = 1;

void setup()
{
	for (int i = 0; i < n; ++i)
	{
		pinMode(pins[i], OUTPUT);
	}
}

int from = 0;
int to = 1;

void loop()
{
	// change pins values
	vals[from] = max(vals[from] -= val_increment, 0);
	vals[to] = min(vals[to] += val_increment, 255);
	analogWrite(pins[from], vals[from]);
	analogWrite(pins[to], vals[to]);
	// change pin
	if (vals[from] == 0 && vals[to] == 255)
	{
		from = to;
		to = (to + 1) % n;
	}
	// delay
	delay(delay_ms);
}
