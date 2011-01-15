/****************************************************************************
** kpk2cmdWidget meta object code from reading C++ file 'kpk2cmdwidget.h'
**
** Created: Tue Jan 11 10:22:44 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "kpk2cmdwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *kpk2cmdWidget::className() const
{
    return "kpk2cmdWidget";
}

QMetaObject *kpk2cmdWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_kpk2cmdWidget( "kpk2cmdWidget", &kpk2cmdWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString kpk2cmdWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "kpk2cmdWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString kpk2cmdWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "kpk2cmdWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* kpk2cmdWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = kpk2cmdWidgetBase::staticMetaObject();
    static const QUMethod slot_0 = {"button_clicked", 0, 0 };
    static const QUMethod slot_1 = {"programChipButton", 0, 0 };
    static const QUMethod slot_2 = {"readChipButton", 0, 0 };
    static const QUParameter param_slot_3[] = {
	{ "index", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_3 = {"partComboBox", 1, param_slot_3 };
    static const QUParameter param_slot_4[] = {
	{ "familyNum", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"familyComboBox", 1, param_slot_4 };
    static const QUMethod slot_5 = {"timerDone", 0, 0 };
    static const QUParameter param_slot_6[] = {
	{ "state", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"preserveEEDataCheckbox", 1, param_slot_6 };
    static const QUParameter param_slot_7[] = {
	{ "state", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_7 = {"configurationMemoryCheckbox", 1, param_slot_7 };
    static const QUParameter param_slot_8[] = {
	{ "state", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_8 = {"idMemoryCheckbox", 1, param_slot_8 };
    static const QUParameter param_slot_9[] = {
	{ "state", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_9 = {"eepromCheckBox", 1, param_slot_9 };
    static const QUParameter param_slot_10[] = {
	{ "state", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"programMemoryCheckbox", 1, param_slot_10 };
    static const QUMethod slot_11 = {"stopButton", 0, 0 };
    static const QUMethod slot_12 = {"runButton", 0, 0 };
    static const QUMethod slot_13 = {"blankCheckButton", 0, 0 };
    static const QUMethod slot_14 = {"eraseChipButton", 0, 0 };
    static const QUMethod slot_15 = {"pk2cmdStdout", 0, 0 };
    static const QUMethod slot_16 = {"pk2cmdFinished", 0, 0 };
    static const QUMethod slot_17 = {"verifyChipButton", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "button_clicked()", &slot_0, QMetaData::Public },
	{ "programChipButton()", &slot_1, QMetaData::Public },
	{ "readChipButton()", &slot_2, QMetaData::Public },
	{ "partComboBox(int)", &slot_3, QMetaData::Public },
	{ "familyComboBox(int)", &slot_4, QMetaData::Public },
	{ "timerDone()", &slot_5, QMetaData::Public },
	{ "preserveEEDataCheckbox(bool)", &slot_6, QMetaData::Public },
	{ "configurationMemoryCheckbox(bool)", &slot_7, QMetaData::Public },
	{ "idMemoryCheckbox(bool)", &slot_8, QMetaData::Public },
	{ "eepromCheckBox(bool)", &slot_9, QMetaData::Public },
	{ "programMemoryCheckbox(bool)", &slot_10, QMetaData::Public },
	{ "stopButton()", &slot_11, QMetaData::Public },
	{ "runButton()", &slot_12, QMetaData::Public },
	{ "blankCheckButton()", &slot_13, QMetaData::Public },
	{ "eraseChipButton()", &slot_14, QMetaData::Public },
	{ "pk2cmdStdout()", &slot_15, QMetaData::Public },
	{ "pk2cmdFinished()", &slot_16, QMetaData::Public },
	{ "verifyChipButton()", &slot_17, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"kpk2cmdWidget", parentObject,
	slot_tbl, 18,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_kpk2cmdWidget.setMetaObject( metaObj );
    return metaObj;
}

void* kpk2cmdWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "kpk2cmdWidget" ) )
	return this;
    return kpk2cmdWidgetBase::qt_cast( clname );
}

bool kpk2cmdWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: button_clicked(); break;
    case 1: programChipButton(); break;
    case 2: readChipButton(); break;
    case 3: partComboBox((int)static_QUType_int.get(_o+1)); break;
    case 4: familyComboBox((int)static_QUType_int.get(_o+1)); break;
    case 5: timerDone(); break;
    case 6: preserveEEDataCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 7: configurationMemoryCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 8: idMemoryCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 9: eepromCheckBox((bool)static_QUType_bool.get(_o+1)); break;
    case 10: programMemoryCheckbox((bool)static_QUType_bool.get(_o+1)); break;
    case 11: stopButton(); break;
    case 12: runButton(); break;
    case 13: blankCheckButton(); break;
    case 14: eraseChipButton(); break;
    case 15: pk2cmdStdout(); break;
    case 16: pk2cmdFinished(); break;
    case 17: verifyChipButton(); break;
    default:
	return kpk2cmdWidgetBase::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool kpk2cmdWidget::qt_emit( int _id, QUObject* _o )
{
    return kpk2cmdWidgetBase::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool kpk2cmdWidget::qt_property( int id, int f, QVariant* v)
{
    return kpk2cmdWidgetBase::qt_property( id, f, v);
}

bool kpk2cmdWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
