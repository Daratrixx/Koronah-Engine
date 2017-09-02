
#ifndef SCRIPTNODE_H
#define SCRIPTNODE_H

#include "Types.h"

union ScriptValue {
    Integer integer;
    Real real;
    String str;
    Point point;
    Region region;
    void* object;
};

class ScriptNode {
public:
    ScriptNode() {
        
    }
    ~ScriptNode() {
        
    }
    
    virtual ScriptNode* call(ScriptNode** parameter) {
        return this;
    }
    virtual ScriptValue getValue() {
        return 0;
    }
    
};

class ScriptValueNode : public ScriptNode {
    ScriptValueNode() : ScriptNode() {
        
    }
    ScriptValueNode(ScriptValue value) : ScriptNode() {
        this->value = value;
    }
    ~ScriptValueNode();
    
    virtual ScriptNode* call(ScriptNode** parameter) {
        return this;
    }
    virtual ScriptValue getValue() {
        return value;
    }
private:
    ScriptValue value;
};

class ScriptFunctionNode : public ScriptNode {
    ScriptValueNode() : ScriptNode() {
        
    }
    ScriptValueNode(ScriptValue(*function)(ScriptNode**)) : ScriptNode() {
        this->function = function;
    }
    ~ScriptValueNode();
    
    virtual ScriptNode* call(ScriptNode** parameter) {
        value = function(parameter);
        return this;
    }
    virtual ScriptValue getValue() {
        return value;
    }
private:
    ScriptValue value;
    ScriptValue(*function)(ScriptNode**);
};

#endif /* SCRIPTNODE_H */
