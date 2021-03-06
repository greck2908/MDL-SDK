/***************************************************************************************************
 * Copyright (c) 2012-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **************************************************************************************************/

#ifndef IO_SCENE_MDL_ELEMENTS_I_MDL_ELEMENTS_COMPILED_MATERIAL_H
#define IO_SCENE_MDL_ELEMENTS_I_MDL_ELEMENTS_COMPILED_MATERIAL_H

#include <io/scene/scene/i_scene_scene_element.h>

#include <mi/base/handle.h>
#include <mi/base/uuid.h>
#include <base/data/db/i_db_tag.h>
#include <base/data/db/i_db_transaction.h>
#include <mi/mdl/mdl_generated_dag.h>

#include <string>

#include "i_mdl_elements_expression.h" // needed by Visual Studio

namespace mi { namespace mdl { class IGenerated_code_lambda_function; } }

namespace MI {

namespace MDL {

class IExpression;
class IExpression_factory;
class IExpression_list;
class IType_factory;
class IValue;
class IValue_factory;
class IValue_list;

/// The class ID for the #Mdl_compiled_material class.
static const SERIAL::Class_id ID_MDL_COMPILED_MATERIAL = 0x5f436d69; // '_Cmi'

class Mdl_compiled_material
  : public SCENE::Scene_element<Mdl_compiled_material, ID_MDL_COMPILED_MATERIAL>
{
public:

    /// Default constructor.
    ///
    /// Does not create a valid instance, to be used by the deserializer only.
    Mdl_compiled_material();

    /// Constructor.
    ///
    /// \param transaction                 The DB transaction to use.
    /// \param instance                    The wrapped MDL material instance.
    /// \param module_filename             The filename of the module.
    /// \param module_name                 The fully-qualified MDL module name.
    /// \param mdl_meters_per_scene_unit   Conversion ratio between meters and scene units.
    /// \param mdl_wavelength_min          The smallest supported wavelength.
    /// \param mdl_wavelength_max          The largest supported wavelength.
    Mdl_compiled_material(
        DB::Transaction* transaction,
        const mi::mdl::IGenerated_code_dag::IMaterial_instance* instance,
        const char* module_filename,
        const char* module_name,
        mi::Float32 mdl_meters_per_scene_unit,
        mi::Float32 mdl_wavelength_min,
        mi::Float32 mdl_wavelength_max);

    // methods corresponding to mi::neuraylib::ICompiled_material

    const IExpression_direct_call* get_body() const;

    mi::Size get_temporary_count() const;

    const IExpression* get_temporary( mi::Size index) const;

    mi::Float32 get_mdl_meters_per_scene_unit() const;

    mi::Float32 get_mdl_wavelength_min() const;

    mi::Float32 get_mdl_wavelength_max() const;

    bool depends_on_state_transform() const;

    bool depends_on_state_object_id() const;

    bool depends_on_global_distribution() const;

    mi::Size get_parameter_count() const;

    char const* get_parameter_name( mi::Size index) const;

    const IValue* get_argument( mi::Size index) const;

    mi::base::Uuid get_hash() const;

    mi::base::Uuid get_slot_hash( mi::Uint32 slot) const;

    const IValue_list* get_arguments() const;

    DB::Tag get_connected_function_db_name(
        DB::Transaction* transaction,
        DB::Tag material_instance_tag,
        const std::string& path) const;

    // internal methods

    const IExpression_list* get_temporaries() const;

    /// Swaps *this and \p other.
    ///
    /// Used by the API to move the content of just constructed DB elements into the already
    /// existing API wrapper.
    void swap( Mdl_compiled_material& other);

    /// Looks up a sub-expression of the compiled material.
    ///
    /// \param transaction     The DB transaction used to access the parameter types of direct
    ///                        calls.
    /// \param path            The path to follow in the body of this compiled material. The path
    ///                        may contain dots or bracket pairs as separators. The path component
    ///                        up to the next separator is used to select struct fields or direct
    ///                        call arguments by name or other compound elements by index.
    /// \param type_factory    The type factory. Used to obtain the initial material struct type.
    /// \param[out] sub_type   The address to store the MDL type corresponding to the
    ///                        return value.
    /// \return                A sub-expression for \p expr according to \p path, or \c NULL in case
    ///                        of errors.
    const IExpression* lookup_sub_expression(
        DB::Transaction* transaction,
        const char* path,
        mi::mdl::IType_factory* type_factory,
        const mi::mdl::IType** sub_type) const;

    /// Looks up a sub-expression of the compiled material.
    ///
    /// Same as overload above, but without the sub-type computation.
    const IExpression* lookup_sub_expression( const char* path) const;

    /// Improved version of SERIAL::Serializable::dump().
    ///
    /// \param transaction   The DB transaction (for name lookups and tag versions). Can be \c NULL.
    void dump( DB::Transaction* transaction) const;

    // methods of SERIAL::Serializable

    const SERIAL::Serializable* serialize( SERIAL::Serializer* serializer) const;

    SERIAL::Serializable* deserialize( SERIAL::Deserializer* deserializer);

    void dump() const { dump( /*transaction*/ 0); }

    // methods of DB::Element_base

    size_t get_size() const;

    DB::Journal_type get_journal_flags() const;

    Uint bundle( DB::Tag* results, Uint size) const;

    // methods of SCENE::Scene_element_base

    void get_scene_element_references( DB::Tag_set* result) const;

    mi::mdl::IGenerated_code_dag::IMaterial_instance::Properties get_properties() const {
        return m_properties;
    }

private:

    /// Converts a hash from the MDL API representation to the base API representation.
    static mi::base::Uuid convert_hash(
        const mi::mdl::DAG_hash& hash);

    mi::base::Handle<IType_factory> m_tf;             ///< The type factory.
    mi::base::Handle<IValue_factory> m_vf;            ///< The value factory.
    mi::base::Handle<IExpression_factory> m_ef;       ///< The expression factory.

    mi::base::Handle<IExpression_direct_call> m_body; ///< The material body.
    mi::base::Handle<IExpression_list> m_temporaries; ///< The temporaries.
    mi::base::Handle<IValue_list> m_arguments;        ///< The arguments.

    mi::base::Uuid m_hash;                            ///< The hash value.
                                                      ///  The hash values for the slots.
    mi::base::Uuid m_slot_hashes[mi::mdl::IGenerated_code_dag::IMaterial_instance::MS_LAST+1];

    mi::Float32 m_mdl_meters_per_scene_unit;          ///< The conversion ratio.
    mi::Float32 m_mdl_wavelength_min;                 ///< The smallest supported wavelength.
    mi::Float32 m_mdl_wavelength_max;                 ///< The largest supported wavelength.

    mi::mdl::IGenerated_code_dag::IMaterial_instance::Properties
        m_properties;                                 ///< Instance properties.
};

} // namespace MDL

} // namespace MI

#endif // IO_SCENE_MDL_ELEMENTS_I_MDL_ELEMENTS_COMPILED_MATERIAL_H
