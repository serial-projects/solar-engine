#include "Logica/Logica.hpp"
#include "Fera/Types/Mesh.hpp"

#include <iostream>

Fera::Types::Mesh::Value* Fera::Types::Mesh::Create(
    const Logica::Texting::SplitResult& result
)
{
    /* Let's traverse everything: */
    Fera::Types::Mesh::Value* current_value = this->root;
    Fera::Types::Mesh::Value* created_value = nullptr;
    
    /**
     * Requirements for an Value to be created:
     *  1-) Last Element must be a value that is a GROUP;
     *  2-) The middle elements or start value must be a GROUP.
     * In the case the mid elements doesn't exist, make them be GROUPS by default.
     */
    for(Fera::Types::Basic::U8 index = 0; index < UINT8_MAX; index++)
    {
        if(index >= (result.size() - 1))
        {
            std::cout << "END reached\n";
            if(current_value->type == Fera::Types::Mesh::Value::Types::GROUP)
            {
                /**
                 * Since we are +1 on the key index, we rewind to the last entry.
                 */
                Fera::Types::Basic::String current_key = result.at(index);
                Fera::Types::Mesh::Value::Group* current_group =
                    static_cast<Fera::Types::Mesh::Value::Group*>(
                        current_value->value
                    );
                if(current_group->find(current_key) != current_group->end())
                {
                    /**
                     * In this case, we just return the element.
                     */
                    std::cout
                        << __PRETTY_FUNCTION__
                        << ": Using already existing object = "
                        << current_key
                        << "\n";
                    created_value = current_group->at(current_key);
                }
                else
                {
                    /**
                     * In this case, the element was not created and we need to do it here.
                     */
                    std::cout
                        << __PRETTY_FUNCTION__
                        << ": Creating an object = "
                        << current_key
                        << "\n";
                    created_value           = new Fera::Types::Mesh::Value;
                    created_value->type     = Fera::Types::Mesh::Value::Types::UNIT;
                    created_value->value    = new Fera::Types::Mesh::Unit;
                    current_group->insert({current_key, created_value});
                }
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            std::cout << "NEXT reached\n";
            /**
             * NOTE: Here the things get an bit complicated, we want to:
             * 1-) Is the current value we are an GROUP?
             *  1.1) If yes, then:
             *      1.1.1) Does the value on key[index] exists in this map?
             *      1.1.2) If it doesn't then, create a new group and keep going.
             *  1.2) If not, then:
             *      1.2.1) Leave the loop, the value is possibly an UNIT.
             */
            if(current_value->type == Fera::Types::Mesh::Value::Types::GROUP)
            {
                Fera::Types::Basic::String current_key = result.at(index);
                Fera::Types::Mesh::Value::Group* current_group =
                    static_cast<Fera::Types::Mesh::Value::Group*>(current_value->value);
                if(current_group->find(current_key) == current_group->end())
                {
                    /**
                     * In this case, we create an new group to hold our content, we also add it to
                     * the branch the value is lacking and use that to the next current value.
                     */
                    std::cout
                        << __PRETTY_FUNCTION__
                        << ": Creating an new group = "
                        << current_key
                        << "\n";
                    Fera::Types::Mesh::Value* new_group = new Fera::Types::Mesh::Value;
                    new_group->type                     = Fera::Types::Mesh::Value::Types::GROUP;
                    new_group->value                    = static_cast<void*>(new Fera::Types::Mesh::Value::Group);
                    current_group->insert({current_key, new_group});
                    current_value = new_group;
                }
                else
                {
                    std::cout
                        << __PRETTY_FUNCTION__
                        << ": Using group = "
                        << current_key
                        << "\n";
                    current_value = current_group->at(current_key);
                }
            }
            else
                break;
        }
    }

    return created_value;
}

Fera::Types::Mesh::Value* Fera::Types::Mesh::Create(
    const Fera::Types::Basic::String& key
)
{
    Logica::Texting::SplitResult result =
        Logica::Texting::Split(key, '.');
    return this->Create(result);
}

Fera::Types::Mesh::Value* Fera::Types::Mesh::Create(
    const Logica::Types::Basic::CH8* key
)
{
    return this->Create(Fera::Types::Basic::String(key));
}