#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	Color clearColor = Color::Black;
	Color color = Color(0, 102, 0, 255);
	Color glass = Color::Cyan;
	Color brown = Color(165, 42, 42, 255);

	int blockw = 200;
	int blockh = 20;

	int trh = blockw * 3 / 4;
	int trRadius = (trh << 1) / 3;

	ContextSettings settings;
	settings.antialiasingLevel = 8;
	RenderWindow window(VideoMode(blockw + 50, ((blockh + trh) << 1) + 50), "SFML Works!", Style::Default, settings);

	RectangleShape r1;
	r1.setFillColor(color);
	r1.setPosition(0, 0);
	r1.setSize(Vector2f(blockw, blockh));
	
	CircleShape tr1(trRadius, 3);
	tr1.setFillColor(glass);
	tr1.setPosition(0, blockh);
	Transform t;
	t.rotate(180.0f, tr1.getPosition().x + (blockw >> 1), tr1.getPosition().y + trRadius);
	t.translate(0, trh / 3);

	CircleShape tr2(trRadius, 3);
	tr2.setFillColor(glass);
	tr2.setPosition(Vector2f(0, tr1.getPosition().y + trh));

	RectangleShape r2;
	r2.setFillColor(color);
	r2.setPosition(0, tr2.getPosition().y + trh);
	r2.setSize(r1.getSize());

	CircleShape tr10(trRadius, 3);
	tr10.setPosition(tr1.getPosition());
	tr10.move(-0.7, 0);
	tr10.setFillColor(brown);

	CircleShape tr20(trRadius, 3);
	tr20.setPosition(tr2.getPosition());
	tr20.move(0, trh);
	tr20.setFillColor(brown);

	RectangleShape c;
	c.setSize(Vector2f(blockw, trh));
	c.setPosition(0, r2.getPosition().y + r2.getSize().y);
	c.setFillColor(clearColor);

	Time delay = milliseconds(50);
	Event event;
	while (window.isOpen())
	{
		window.clear(clearColor);
		window.draw(r1);
		window.draw(tr1, t);
		window.draw(tr2);

		window.draw(tr10, t);
		window.draw(tr20);

		window.draw(r2);

		window.draw(c);
		window.display();

		window.waitEvent(event);
		do {
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed ) {
				if (event.key.code == sf::Keyboard::Space) {
					
					tr10.setRadius(trRadius);
					tr10.setPosition(tr1.getPosition());
					tr10.move(-0.7, 0);
					tr20.setPosition(tr2.getPosition());
					tr20.move(0, trh);

					for (int progress = 0; progress < trh; progress++) {
						window.clear(clearColor);
						window.draw(r1);
						window.draw(tr1, t);
						window.draw(tr2);

						window.draw(tr10, t);
						window.draw(tr20);

						window.draw(r2);
						window.draw(c);
						window.display();

						float nr = trRadius - 0.7 * progress;
						if (nr < 0)
							nr = 0;
						tr10.setRadius(nr);
						tr10.move(0.7, 0);
						tr20.move(0, -1);

						sleep(delay);
					}
				}
			}
		} while (window.pollEvent(event));
	}
	return 0;
}