/****************************************************************************
** preferenceswidgetbase meta object code from reading C++ file 'preferencewidgetbase.h'
**
** Created: Tue Jan 11 10:22:45 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "preferencewidgetbase.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *preferenceswidgetbase::className() const
{
    return "preferenceswidgetbase";
}

QMetaObject *preferenceswidgetbase::metaObj = 0;
static QMetaObjectCleanUp cleanUp_preferenceswidgetbase( "preferenceswidgetbase", &preferenceswidgetbase::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString preferenceswidgetbase::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "preferenceswidgetbase", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString preferenceswidgetbase::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "preferenceswidgetbase", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* preferenceswidgetbase::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"cancelButton", 0, 0 };
    static const QUMethod slot_1 = {"saveButton", 0, 0 };
    static const QUParameter param_slot_2[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"dashTeeCheckbox", 1, param_slot_2 };
    static const QUParameter param_slot_3[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"dashArrCheckBox", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"restoreLastMicroCheckbox", 1, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"haltMicroCheckbox", 1, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"programmingEraseCheckbox", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "check", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"programmingVerifyCheckbox", 1, param_slot_7 };
    static const QUMethod slot_8 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "cancelButton()", &slot_0, QMetaData::Public },
	{ "saveButton()", &slot_1, QMetaData::Public },
	{ "dashTeeCheckbox(bool)", &slot_2, QMetaData::Public },
	{ "dashArrCheckBox(bool)", &slot_3, QMetaData::Public },
	{ "restoreLastMicroCheckbox(bool)", &slot_4, QMetaData::Public },
	{ "haltMicroCheckbox(bool)", &slot_5, QMetaData::Public },
	{ "programmingEraseCheckbox(bool)", &slot_6, QMetaData::Public },
	{ "programmingVerifyCheckbox(bool)", &slot_7, QMetaData::Public },
	{ "languageChange()", &slot_8, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"preferenceswidgetbase", parentObject,
	slot_tbl, 9,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_preferenceswidgetbase.setMetaObject( metaObj );
    return metaObj;
}

void* preferenceswidgetbase::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "preferenceswidgetbase" ) )
	return this;
    return QDialog::qt_cast( clname );
}

bool preferenceswidgetbase::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: cancelButton(); break;
    case 1: saveButton(); break;
    case 2: dashTeeCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 3: dashArrCheckBox((bool)static_QUType_bool.get(_o+1)); break;
    case 4: restoreLastMicroCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 5: haltMicroCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 6: programmingEraseCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 7: programmingVerifyCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 8: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool preferenceswidgetbase::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool preferenceswidgetbase::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool preferenceswidgetbase::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
