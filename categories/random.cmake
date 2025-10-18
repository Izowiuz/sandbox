create_sandbox_target("random" "virtual-destructor")
create_sandbox_target("random" "const-span")
create_sandbox_target("random" "fold-expressions")
create_sandbox_target("random" "structured-bindings")
create_sandbox_target("random" "structs-padding")
create_sandbox_target("random" "modules-test"
ADDITIONAL_COMPILE_FLAGS
    "-fmodules-ts"
)
create_sandbox_target("random" "ref-qualifiers")
