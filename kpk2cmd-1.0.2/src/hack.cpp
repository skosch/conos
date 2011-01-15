
// This is a hack to make rebuilding this work. Note that during the build process this gets tacked on to the
// uic_image_collection.cpp file.

QImage canna_findImage( const QString& name )
{
	return(uic_findImage(name));
}

