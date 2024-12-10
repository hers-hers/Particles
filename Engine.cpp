#include "Engine.h"

////////////////////////////////////////////////////////////////
////////////// TODO: ///////////////////////////////////////////
////////////////////////////////////////////////////////////////

Engine::Engine() {
	m_Window.create(VideoMode::getDesktopMode(), "Particle Engine");
}



void Engine::run() {
	Clock clock;
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete. Starting engine..." << endl;

	while (m_Window.isOpen()) {
		Time dt = clock.restart();
		float dtAsSeconds = dt.asSeconds();
		input();
		update(dtAsSeconds);
		draw();
	}
}




void Engine::input() {
	Event event;
	while (m_Window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			m_Window.close();
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
			m_Window.close();
		}
		if (event.type == Event::MouseButtonPressed &&
			event.mouseButton.button == Mouse::Left) {
			Vector2i mouseClickPosition = Mouse::getPosition(m_Window);

			for (int i = 0; i < 5; i++) {
				int numPoints = 25 + (rand() % 50);
				m_particles.emplace_back(m_Window, numPoints, mouseClickPosition);
			}
		}
	}
}





void Engine::update(float dtAsSeconds) {
	for (auto up = m_particles.begin(); up != m_particles.end();) {
		up->update(dtAsSeconds);
		if (up->getTTL() > 0.0) {
			up->update(dtAsSeconds);
			up++;
		}
		else { up = m_particles.erase(up); }
	}
}





void Engine::draw() {
	m_Window.clear();
	for (auto& particle : m_particles) {
		m_Window.draw(particle);
	}
	m_Window.display();
}