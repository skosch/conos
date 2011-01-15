/****************************************************************************
** kpk2cmdWidgetBase meta object code from reading C++ file 'kpk2cmdwidgetbase.h'
**
** Created: Tue Jan 11 10:22:45 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "kpk2cmdwidgetbase.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *kpk2cmdWidgetBase::className() const
{
    return "kpk2cmdWidgetBase";
}

QMetaObject *kpk2cmdWidgetBase::metaObj = 0;
static QMetaObjectCleanUp cleanUp_kpk2cmdWidgetBase( "kpk2cmdWidgetBase", &kpk2cmdWidgetBase::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString kpk2cmdWidgetBase::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "kpk2cmdWidgetBase", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString kpk2cmdWidgetBase::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "kpk2cmdWidgetBase", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* kpk2cmdWidgetBase::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"familyComboBox", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"partComboBox", 1, param_slot_1 };
    static const QUMethod slot_2 = {"readChipButton", 0, 0 };
    static const QUMethod slot_3 = {"programChipButton", 0, 0 };
    static const QUMethod slot_4 = {"eraseChipButton", 0, 0 };
    static const QUMethod slot_5 = {"blankCheckButton", 0, 0 };
    static const QUMethod slot_6 = {"runButton", 0, 0 };
    static const QUMethod slot_7 = {"stopButton", 0, 0 };
    static const QUParameter param_slot_8[] = {
	{ "state", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"programMemoryCheckbox", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "state", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"eepromCheckBox", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ "state", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"idMemoryCheckbox", 1, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ "state", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"configurationMemoryCheckbox", 1, param_slot_11 };
    static const QUParameter param_slot_12[] = {
	{ "state", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_12 = {"preserveEEDataCheckbox", 1, param_slot_12 };
    static const QUMethod slot_13 = {"verifyChipButton", 0, 0 };
    static const QUMethod slot_14 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "familyComboBox(int)", &slot_0, QMetaData::Public },
	{ "partComboBox(int)", &slot_1, QMetaData::Public },
	{ "readChipButton()", &slot_2, QMetaData::Public },
	{ "programChipButton()", &slot_3, QMetaData::Public },
	{ "eraseChipButton()", &slot_4, QMetaData::Public },
	{ "blankCheckButton()", &slot_5, QMetaData::Public },
	{ "runButton()", &slot_6, QMetaData::Public },
	{ "stopButton()", &slot_7, QMetaData::Public },
	{ "programMemoryCheckbox(bool)", &slot_8, QMetaData::Public },
	{ "eepromCheckBox(bool)", &slot_9, QMetaData::Public },
	{ "idMemoryCheckbox(bool)", &slot_10, QMetaData::Public },
	{ "configurationMemoryCheckbox(bool)", &slot_11, QMetaData::Public },
	{ "preserveEEDataCheckbox(bool)", &slot_12, QMetaData::Public },
	{ "verifyChipButton()", &slot_13, QMetaData::Public },
	{ "languageChange()", &slot_14, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"kpk2cmdWidgetBase", parentObject,
	slot_tbl, 15,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_kpk2cmdWidgetBase.setMetaObject( metaObj );
    return metaObj;
}

void* kpk2cmdWidgetBase::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "kpk2cmdWidgetBase" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool kpk2cmdWidgetBase::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: familyComboBox((int)static_QUType_int.get(_o+1)); break;
    case 1: partComboBox((int)static_QUType_int.get(_o+1)); break;
    case 2: readChipButton(); break;
    case 3: programChipButton(); break;
    case 4: eraseChipButton(); break;
    case 5: blankCheckButton(); break;
    case 6: runButton(); break;
    case 7: stopButton(); break;
    case 8: programMemoryCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 9: eepromCheckBox((bool)static_QUType_bool.get(_o+1)); break;
    case 10: idMemoryCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 11: configurationMemoryCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 12: preserveEEDataCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 13: verifyChipButton(); break;
    case 14: languageChange(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool kpk2cmdWidgetBase::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool kpk2cmdWidgetBase::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool kpk2cmdWidgetBase::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
