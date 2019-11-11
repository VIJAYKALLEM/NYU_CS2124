#ifndef Instrument_h
#define Instrument_h
namespace Music{
    class Instrument{
    public:
        virtual void makeSound() const;
        virtual void play() const = 0;
    };

    class Brass : public Instrument{
    public:
        Brass(unsigned mouthpiece_size);
        void makeSound() const;
        virtual void play() const = 0;
    private:
        unsigned mouthpiece_size;
    };

    class String : public Instrument{
    public:
        String(unsigned pitch);
        void makeSound() const;
        virtual void play() const = 0;
    private:
        unsigned pitch;
    };

    class Percussion : public Instrument{
    public:
        void makeSound() const;
        virtual void play() const = 0;
    };

    class Violin : public String{
        using String::String;
        void play() const;
    };
    class Trumpet: public Brass{
        using Brass::Brass;
        void play() const;
    };
    class Trombone: public Brass{
        using Brass::Brass;
        void play() const;
    };
    class Cello: public String{
        using String::String;
        void play() const;
    };
    class Cymbal: public Percussion{
        using Percussion::Percussion;
        void play() const;
    };
    class Drum: public Percussion{
        using Percussion::Percussion;
        void play() const;
    };
}
#endif /* Instrument_h */
