/****************************************************************************
** kpk2cmd meta object code from reading C++ file 'kpk2cmd.h'
**
** Created: Tue Jan 11 10:22:44 2011
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.8   edited Feb 2 14:59 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "kpk2cmd.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.8b. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *kpk2cmd::className() const
{
    return "kpk2cmd";
}

QMetaObject *kpk2cmd::metaObj = 0;
static QMetaObjectCleanUp cleanUp_kpk2cmd( "kpk2cmd", &kpk2cmd::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString kpk2cmd::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "kpk2cmd", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString kpk2cmd::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "kpk2cmd", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* kpk2cmd::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"fileAbout", 0, 0 };
    static const QUMethod slot_1 = {"filePreferences", 0, 0 };
    static const QUMethod slot_2 = {"justBeforeQuit", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "fileAbout()", &slot_0, QMetaData::Public },
	{ "filePreferences()", &slot_1, QMetaData::Public },
	{ "justBeforeQuit()", &slot_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"kpk2cmd", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_kpk2cmd.setMetaObject( metaObj );
    return metaObj;
}

void* kpk2cmd::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "kpk2cmd" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool kpk2cmd::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: fileAbout(); break;
    case 1: filePreferences(); break;
    case 2: justBeforeQuit(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool kpk2cmd::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool kpk2cmd::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool kpk2cmd::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
