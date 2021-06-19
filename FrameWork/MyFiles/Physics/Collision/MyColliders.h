#pragma once

#include <vector>
#include "particle.h"
#include "plinks.h"

namespace cyclone {

	class AMyContact : public cyclone::ParticleContactGenerator
	{
	public:
		bool is_trigger = false;

		virtual void init(cyclone::Particle* p, double size) = 0;
		virtual unsigned addContact(cyclone::ParticleContact* contact, unsigned limit) const = 0;
		virtual unsigned int getMaxContactCount();

		void(*onEnter)(cyclone::Particle* contact) = NULL;
		void(*onStay)(cyclone::Particle* contact) = NULL;
		void(*onExit)(cyclone::Particle* contact) = NULL;

	protected:
		mutable std::vector<std::pair<cyclone::Particle*, bool>> particles;
		std::vector<double> size;
	};

	class MyLinesContact : public AMyContact
	{
		std::vector<cyclone::Vector3> map;
	public:
		MyLinesContact(std::vector<cyclone::Vector3> dots);
		~MyLinesContact();
		
		void setDots(std::vector<cyclone::Vector3> dots);

		// Hérité via AMyContact
		void init(cyclone::Particle* p, double size) override;
		virtual unsigned addContact(cyclone::ParticleContact* contact, unsigned limit) const override;
		unsigned int getMaxContactCount() override;

	};

	class MyCircleContact : public AMyContact
	{
	public:
		MyCircleContact();
		~MyCircleContact();

		// Hérité via AMyContact
		void init(cyclone::Particle* p, double size) override;
		virtual unsigned addContact(cyclone::ParticleContact* contact, unsigned limit) const override;
	};

	class MyRectContact : public AMyContact
	{
		cyclone::Vector3 p1;
		cyclone::Vector3 p2;
	public:
		MyRectContact(cyclone::Vector3 p1, cyclone::Vector3 p2);
		~MyRectContact();

		// Hérité via AMyContact
		void init(cyclone::Particle* p, double size) override;
		virtual unsigned addContact(cyclone::ParticleContact* contact, unsigned limit) const override;
	};

}