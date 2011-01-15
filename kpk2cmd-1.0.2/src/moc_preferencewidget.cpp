/****************************************************************************
** preferencewidget meta object code from reading C++ file 'preferencewidget.h'
**
** Created: Tue Jan 11 10:22:44 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "preferencewidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *preferencewidget::className() const
{
    return "preferencewidget";
}

QMetaObject *preferencewidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_preferencewidget( "preferencewidget", &preferencewidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString preferencewidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "preferencewidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString preferencewidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "preferencewidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* preferencewidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = preferenceswidgetbase::staticMetaObject();
    static const QUMethod slot_0 = {"saveButton", 0, 0 };
    static const QUMethod slot_1 = {"cancelButton", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"programmingVerifyCheckbox", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"programmingEraseCheckbox", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"dashTeeCheckbox", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"dashArrCheckBox", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"haltMicroCheckbox", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"restoreLastMicroCheckbox", 1, param_slot_7 };
    static const QMetaData slot_tbl[] = {
	{ "saveButton()", &slot_0, QMetaData::Public },
	{ "cancelButton()", &slot_1, QMetaData::Public },
	{ "programmingVerifyCheckbox(bool)", &slot_2, QMetaData::Public },
	{ "programmingEraseCheckbox(bool)", &slot_3, QMetaData::Public },
	{ "dashTeeCheckbox(bool)", &slot_4, QMetaData::Public },
	{ "dashArrCheckBox(bool)", &slot_5, QMetaData::Public },
	{ "haltMicroCheckbox(bool)", &slot_6, QMetaData::Public },
	{ "restoreLastMicroCheckbox(bool)", &slot_7, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"preferencewidget", parentObject,
	slot_tbl, 8,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_preferencewidget.setMetaObject( metaObj );
    return metaObj;
}

void* preferencewidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "preferencewidget" ) )
	return this;
    return preferenceswidgetbase::qt_cast( clname );
}

bool preferencewidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: saveButton(); break;
    case 1: cancelButton(); break;
    case 2: programmingVerifyCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 3: programmingEraseCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 4: dashTeeCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 5: dashArrCheckBox((bool)static_QUType_bool.get(_o+1)); break;
    case 6: haltMicroCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 7: restoreLastMicroCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    default:
	return preferenceswidgetbase::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool preferencewidget::qt_emit( int _id, QUObject* _o )
{
    return preferenceswidgetbase::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool preferencewidget::qt_property( int id, int f, QVariant* v)
{
    return preferenceswidgetbase::qt_property( id, f, v);
}

bool preferencewidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
