#include "Logica/Logica.hpp"
#include "Sojson/Sojson.hpp"
#include "Fera/Fera.hpp"

#include <iostream>

namespace App
{
    /**
     * \brief Perform the Testings on the Logica Subsystem:
     */
    void PerformLogicaTesting()
    {
        /* Set the stream: */
        Logica::Types::Stream::File f;
        f.SetFile("./Root/Settings.jsonc");
        
        /* Set the tokenizer/instance: */
        Logica::Texting::Tokenizer::Instance i;
        Logica::Texting::Tokenizer::Rules r;
        r.get_character_type = 
            [](Logica::Types::Basic::I32 ch)
            {
                Logica::Types::Basic::U8 value =
                    Logica::Texting::Tokenizer::Rules::CharacterTypes::NOTHING;
                switch(ch)
                {
                    case '\n': case '\t': case ' ':
                        value = Logica::Texting::Tokenizer::Rules::CharacterTypes::TOKEN_DELIMITER;
                        break;
                    case '\'': case '"':
                        value = Logica::Texting::Tokenizer::Rules::CharacterTypes::STRING_DELIMITER;
                        break;
                    case '[': case ']': case '{': case '}': case '/':
                        value = Logica::Texting::Tokenizer::Rules::CharacterTypes::HIGHLIGHT_TOKEN;
                        break;
                };
                return value;
            };
        r.comment_token                     = '/';
        r.line_comment_hint_token           = '/';
        r.delimited_comment_hint_token      = '*';
        r.delimited_comment_closure_token   = '*';

        i.SetBuffer(&f);
        i.SetRules(&r);

        Logica::Types::Basic::String source;
        for(
            Logica::Types::Basic::U32 index = 0;
            (i.state == Logica::Texting::Tokenizer::Instance::States::RUNNING);
            index++
        )
        {
            i.GetToken(&source);
            std::cout
                << index
                << ": "
                << source
                << "\n";
        }

        f.UnsetFile();
    }
    void PerformLogicaTestingButUsingAnotherRuleset()
    {
        /* Set the stream: */
        Logica::Types::Stream::File f;
        if(!f.SetFile("./Root/bk.py"))
            return;
        
        /* Set the tokenizer/instance: */
        Logica::Texting::Tokenizer::Instance i;
        Logica::Texting::Tokenizer::Rules r;
        r.get_character_type = 
            [](Logica::Types::Basic::I32 ch)
            {
                Logica::Types::Basic::U8 value =
                    Logica::Texting::Tokenizer::Rules::CharacterTypes::NOTHING;
                switch(ch)
                {
                    case '\n': case '\t': case ' ':
                        value = Logica::Texting::Tokenizer::Rules::CharacterTypes::TOKEN_DELIMITER;
                        break;
                    case '\'': case '"':
                        value = Logica::Texting::Tokenizer::Rules::CharacterTypes::STRING_DELIMITER;
                        break;
                    case '[': case ']': case '{': case '}':
                        value = Logica::Texting::Tokenizer::Rules::CharacterTypes::HIGHLIGHT_TOKEN;
                        break;
                };
                return value;
            };
        r.comment_token                     = '#';
        r.line_comment_hint_token           = 0;
        r.delimited_comment_hint_token      = 0;
        r.delimited_comment_closure_token   = 0;

        i.SetBuffer(&f);
        i.SetRules(&r);

        Logica::Types::Basic::String source;
        for(
            Logica::Types::Basic::U32 index = 0;
            (i.state == Logica::Texting::Tokenizer::Instance::States::RUNNING);
            index++
        )
        {
            i.GetToken(&source);
            std::cout
                << index
                << ": "
                << source
                << "\n";
        }
    }

    void PerformSojsonTesting()
    {
        /* Set the stream: */
        Logica::Types::Stream::File f;
        if(!f.SetFile("./Root/A.jsonc"))
        {
            std::cerr
                << __PRETTY_FUNCTION__
                << ": Failed to open!\n";
            std::abort();
        }

        Sojson::Decode::Instance instance;
        instance.SetBuffer(&f);

        Sojson::Node* tree = instance.Parse();
        
        if(instance.GetState() == Sojson::Decode::Instance::DIED)
        {
            std::cout
                << __PRETTY_FUNCTION__
                << ": "
                << instance.validator.GetErrorLog()
                << "\n";
        }
        else
        {
            std::cout
                << __PRETTY_FUNCTION__
                << ": "
                << tree->Dump()
                << "\n";
        }
        
        //tree->Cleanup();
        delete tree;
    }

    void PerformFeraTestOnMesh()
    {
        Fera::Types::Mesh* m_mesh = new Fera::Types::Mesh;
        m_mesh->Create("default.object");
        
        /* Append some values inside: */
        Fera::Types::Mesh::Value* default_object = m_mesh->Get("default.object");
        if(default_object)
        {
            if(default_object->type == Fera::Types::Mesh::Value::Types::UNIT)
                static_cast<Fera::Types::Mesh::Unit*>(default_object->value)->faces = 30;
            else
            {
                std::cout
                    << __PRETTY_FUNCTION__
                    << ": expected unit but got group.\n";
            }
        }
        else
        {
            std::cout
                << __PRETTY_FUNCTION__
                << ": adquired bad object!\n";
        }

        /* Say what is inside; */
        std::cout 
            << __PRETTY_FUNCTION__
            << ": "
            << m_mesh->Dump()
            << "\n";
        delete m_mesh;
    }

    void PerformTest()
    {
        // App::PerformLogicaTesting();
        // App::PerformLogicaTestingButUsingAnotherRuleset();
        // App::PerformSojsonTesting();
        App::PerformFeraTestOnMesh();
    }
};

int main(int argc, char* argv[])
{
    App::PerformTest();
    return 0;
}