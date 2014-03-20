#ifndef ANAX_EXAMPLES_MOVEMENT_PLAYERINPUTSYSTEM_HPP
#define ANAX_EXAMPLES_MOVEMENT_PLAYERINPUTSYSTEM_HPP

#include <anax/System.hpp>

#include "PlayerComponent.hpp"

struct PlayerInputSystem : anax::System<PlayerInputSystem>
{
public:
	
	struct Listener
	{
		virtual void onPlayerStateChanged(anax::Entity& e, PlayerComponent::State state) = 0;
	};

	PlayerInputSystem();
	
	void update(double deltaTime);
	
	void addListener(Listener* listener) { m_Listeners.push_back(listener); }
	void removeListener(Listener* listener) { m_Listeners.erase(std::remove(m_Listeners.begin(), m_Listeners.end(), listener), m_Listeners.end()); }

private:
	
	void setPlayerState(anax::Entity& e, PlayerComponent& pc, PlayerComponent::State);

	std::vector<Listener*> m_Listeners;
};

#endif
