#ifndef SojsonTypesNode_hpp
#define SojsonTypesNode_hpp

#include "Sojson/Types/Basic.hpp"
#include <unordered_map>
#include <functional>

namespace Sojson
{
    class Node
    {
        private:

        /**
         * \brief Will search for the object on the current index!
         */
        Sojson::Node* RecursiveSearch(
            Sojson::Node* node,
            const Logica::Texting::SplitResult& key,
            const Sojson::Types::Basic::U8 depth
        );

        public:

        /* TYPES: */

        typedef Sojson::Types::Basic::I32                                       Integer;
        typedef Sojson::Types::Basic::F32                                       Decimal;
        typedef Sojson::Types::Basic::String                                    String;
        typedef Sojson::Types::Basic::U8                                        Boolean;
        typedef std::vector<Sojson::Node*>                                      List;
        typedef std::unordered_map<Sojson::Types::Basic::String, Sojson::Node*> Table;

        /* SET */

        void SetIntegerValue(const Sojson::Node::Integer value);
        void SetDecimalValue(const Sojson::Node::Decimal value);
        void SetStringValue(const Sojson::Node::String& value);
        void SetBooleanValue(const Sojson::Node::Boolean value);
        void SetNullValue();
        Sojson::Node::List* CreateList();
        Sojson::Node::Table* CreateTable();

        /* CASTING: */
        std::optional<Sojson::Node::Integer> CastInteger();
        std::optional<Sojson::Node::Decimal> CastDecimal();
        std::optional<Sojson::Node::String> CastString();
        std::optional<Sojson::Node::Boolean> CastBoolean();
        std::optional<Sojson::Node::List> CastList();
        std::optional<Sojson::Node::Table> CastTable();

        enum NodeTypes
        {
            NOTHING                 = 0,
            INTEGER,
            DECIMAL,
            STRING,
            BOOLEAN,
            LIST,
            TABLE,
            UNNKNOWN                 = UINT8_MAX
        };

        /**
         * \brief The type the Node is currently holding.
         */
        Sojson::Node::NodeTypes type;

        /**
         * \brief The value the node is point to on the memory.
         */
        void* value;

        /**
         * \brief You must delete the values for the allocated values.
         */
        void Cleanup();

        /**
         * \brief Iterates on the node using an iterator function.
         */
        void Iterate(
            std::function<void(Sojson::Node*)> iterator
        );
        
        /**
         * \brief Will search for the object contained and NULL will be returned in case
         * the object was not found, use '.' to split your keys!
         * 
         * \param key the key to be searched.
         */
        Sojson::Node* Get(
            Sojson::Types::Basic::String& key
        );

        /**
         * \brief Return the node.
         * \param key the key to be searched.
         */
        Sojson::Node* Get(
            const Sojson::Types::Basic::CH8* key
        );

        /**
         * \brief Return an node from an already split object and on a certain depth.
         * 
         * \warning DO NOT USE THIS UNLESS YOU REALLY KNOW WHAT YOU ARE DOING!
         * \dontinclude
         * 
         * \param key the key to be searched (but already result of an split).
         * \param depth the position of the key being access.
         */
        Sojson::Node* Get(
            const Logica::Texting::SplitResult& key,
            const Logica::Types::Basic::U8 depth
        );

        /**
         * \brief Return if the node is an value from the enum NodeTypes
         */
        Sojson::Types::Basic::Result Is(
            Sojson::Node::NodeTypes type
        );

        /**
         * \brief Dump the value on an String buffer:
         */
        Sojson::Types::Basic::String Dump();

        /* Constructor to initialize some basic data: */
        Node();

        /* Destructor to not initialize some data: */
        ~Node();
    };
};

#endif