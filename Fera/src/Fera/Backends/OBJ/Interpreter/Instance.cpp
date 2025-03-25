#include "Fera/Backends/OBJ/Interpreter/Instance.hpp"
#include "Fera/Backends/OBJ/Interpreter/Opcodes.hpp"

#include <iostream>

Fera::Backends::OBJ::Interpreter::Instance Fera::Backends::OBJ::Interpreter::InstanceNew()
{
    Fera::Backends::OBJ::Interpreter::Instance instance;
    return instance;
}

void Fera::Backends::OBJ::Interpreter::InstanceDestroy(
    Fera::Backends::OBJ::Interpreter::Instance* instance
)
{
    /* TODO: this does nothing. */
}

void Fera::Backends::OBJ::Interpreter::InstanceInit(
    Fera::Backends::OBJ::Interpreter::Instance* instance,
    Logica::Types::Buffer::Base* buffer
)
{
    instance->tokenizer_rules = Logica::Texting::Tokenizer::Rules();
    instance->tokenizer_rules.get_token_type = 
    [](
        Logica::Types::Basic::I32 ch
    )
    {
        Logica::Texting::Tokenizer::Rules::TokenTypes type
            = Logica::Texting::Tokenizer::Rules::TokenTypes::NO_TOKEN;
        switch(ch)
        {
            case ' ': case '\n': case '\t':
                type = Logica::Texting::Tokenizer::Rules::TokenTypes::DELIMITER;
                break;
            case '"': case '\'':
                type = Logica::Texting::Tokenizer::Rules::TokenTypes::STRING;
                break;
            default:
                break;
        }
        return type;
    };
    instance->tokenizer_rules.comment_starter           = '#';
    instance->tokenizer_rules.comment_single_line_hint  = 0;
    instance->tokenizer_rules.comment_delimited_hint    = 0;

    /* set the tokenizer: */
    instance->tokenizer = Logica::Texting::Tokenizer::Instance();
    instance->tokenizer.SetRules(&instance->tokenizer_rules);
    instance->tokenizer.SetBuffer(buffer);

    /* set the other elements: */
    instance->current_group     = "default";
    instance->current_object    = "root";
    instance->current_V         = Fera::Backends::OBJ::Interpreter::InstanceLists::V();
    instance->current_VT        = Fera::Backends::OBJ::Interpreter::InstanceLists::VT();
    instance->current_VN        = Fera::Backends::OBJ::Interpreter::InstanceLists::VN();
    
    /* NOTE: this here is the ONLY allocated object! */
    instance->root = Fera::Meshing::MeshNew();
    Fera::Meshing::MeshInit(instance->root);
    Fera::Backends::OBJ::Interpreter::InstanceGenerateObject(instance);

    /* Set the buffer to ONLINE: */
    instance->working_object = Fera::Meshing::MeshUnitTypes::Object();
    instance->state = Fera::Backends::OBJ::Interpreter::InstanceStates::Running;
}

void Fera::Backends::OBJ::Interpreter::InstanceStep(
    Fera::Backends::OBJ::Interpreter::Instance* instance
)
{
    /* DO an single opcode: */
    if(instance->state == Fera::Backends::OBJ::Interpreter::InstanceStates::Running)
    {
        /* then get the opcode: */
        /* Fera::Backends::OBJ::Interpreter:: */
        Fera::Types::String opcode = instance->tokenizer.GetToken(true);
        if(instance->tokenizer.GetState() == Logica::Texting::Tokenizer::Instance::States::RUNNING)
            Fera::Backends::OBJ::Interpreter::InstancePerformOpcode(instance, opcode);
        else
        {
            /* NOTE: since we finished, append the last working_object to the tree! */
            Fera::Backends::OBJ::Interpreter::InstanceGenerateObject(instance);
            instance->state = Fera::Backends::OBJ::Interpreter::InstanceStates::Finished;
        }
    }
}

void Fera::Backends::OBJ::Interpreter::InstanceParse(
    Fera::Backends::OBJ::Interpreter::Instance* instance
)
{
    /* BEGIN parsing: */
    for(
        ;
        (instance->state == Fera::Backends::OBJ::Interpreter::InstanceStates::Running)
        ;
    )
        Fera::Backends::OBJ::Interpreter::InstanceStep(instance);
}

Fera::Meshing::Mesh* Fera::Backends::OBJ::Interpreter::InstanceGetMesh(
    Fera::Backends::OBJ::Interpreter::Instance* instance
)
{
    return instance->root;
}

void Fera::Backends::OBJ::Interpreter::InstanceSetProperty(
    Fera::Backends::OBJ::Interpreter::Instance *instance,
    Fera::Backends::OBJ::Interpreter::Properties properties
)
{
    instance->properties = properties;
}

void Fera::Backends::OBJ::Interpreter::InstanceGenerateObject(
    Fera::Backends::OBJ::Interpreter::Instance* instance
)
{
    /* NOTE: this expects the mesh to be online! */
    Fera::Meshing::MeshUnitTypes::Group* mesh_group = 
        (Fera::Meshing::MeshUnitTypes::Group*)(instance->root->value);
    if(mesh_group->find(instance->current_group) == mesh_group->end())
    {
        /* THEN we should create the new group: */
        Fera::Meshing::MeshUnit* group_unit = 
            Fera::Meshing::MeshUnitNew();
        Fera::Meshing::MeshUnitTypes::Group* group = 
            new Fera::Meshing::MeshUnitTypes::Group;
        Fera::Meshing::MeshUnitInit(
            group_unit,
            (void*)group,
            Fera::Meshing::MeshUnitValueTypes::Group
        );
        mesh_group->insert({ instance->current_group, group_unit });
    }

    /* NOTE: now there is a important decision we need to do:
     * 1-) if the object already exists then:
     * + We should either put the working_object on the object (copy the buffer) or
     * + We should fail, implement this on the rules!
     */
    
    Fera::Meshing::MeshUnit* group_unit = mesh_group->at(instance->current_group);
    Fera::Meshing::MeshUnitTypes::Group* group =
        (Fera::Meshing::MeshUnitTypes::Group*)(group_unit->value);
    
    /* TODO: set an rule to whether this should fail, by default this fails! */
    if(group->find(instance->current_object) == group->end())
    {
        Fera::Meshing::MeshUnit* object_unit = Fera::Meshing::MeshUnitNew();
        Fera::Meshing::MeshUnitTypes::Object* object = 
            new Fera::Meshing::MeshUnitTypes::Object;
        Fera::Meshing::MeshUnitInit(
            object_unit,
            (void*)object,
            Fera::Meshing::MeshUnitValueTypes::Object
        );
        group->insert({instance->current_object, object_unit});
    }
    
    /* Continue to modify the object: */
    Fera::Meshing::MeshUnit* object_unit = group->at(instance->current_object);
    Fera::Meshing::MeshUnitTypes::Object* object = 
        (Fera::Meshing::MeshUnitTypes::Object*)object_unit->value;
    for(auto content : instance->working_object)
        object->push_back(content);
}
