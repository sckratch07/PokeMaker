#include "Core/StateMachine.hpp"
#include "Core/State.hpp"

#include <SFML/Graphics.hpp>

namespace Core
{
    StateMachine::~StateMachine()
    {
        clear();
    }

    void StateMachine::pushState(std::unique_ptr<State> state)
    {
        if (state)
        {
            state->onEnter();
            m_states.push_back(std::move(state));
        }
    }


    void StateMachine::popState()
    {
        if (!m_states.empty())
        {
            m_states.back()->onExit();
            m_states.pop_back();
        }
    }


    void StateMachine::replaceState(std::unique_ptr<State> state)
    {
        popState();
        pushState(std::move(state));
    }


    void StateMachine::clear()
    {
        while (!m_states.empty())
        {
            m_states.back()->onExit();
            m_states.pop_back();
        }
    }


    void StateMachine::update(float dt)
    {
        // Met à jour depuis le sommet jusqu'au premier State bloquant
        for (auto& state : m_states)
        {
            state->update(dt);
            if (state->isBlocking())
                break;
        }
    }


    void StateMachine::render(sf::RenderWindow& window)
    {
        // Rendu depuis le bas jusqu'au sommet
        for (auto& state : m_states)
        {
            state->render(window);
            if (state->isBlocking())
                break;
        }
    }

    void StateMachine::handleEvent(const sf::Event& event)
    {
        // Propage les événements depuis le sommet
        for (auto& state : m_states)
        {
            state->handleEvent(event);
            if (state->isBlocking())
                break;
        }
    }
}