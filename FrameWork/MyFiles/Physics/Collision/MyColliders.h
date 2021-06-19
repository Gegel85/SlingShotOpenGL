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
		unsigned int getMaxContactCount();

		void(*onEnter)(cyclone::Particle* contact);
		void(*onExit)(cyclone::Particle* contact);

	protected:
		std::vector<std::pair<cyclone::Particle*, bool>> particles;
		std::vector<double> size;
	};

	class MyMapContact : public AMyContact
	{
		std::vector<cyclone::Vector3> map;
	public:
		MyMapContact(std::vector<cyclone::Vector3> dots);
		~MyMapContact();

		// Hérité via AMyContact
		void init(cyclone::Particle* p, double size) override;
		void setMap(std::vector<cyclone::Vector3> dots);
		virtual unsigned addContact(cyclone::ParticleContact* contact, unsigned limit) const override;

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