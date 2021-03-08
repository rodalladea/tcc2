import { model } from 'mongoose';
import { XBIDocument } from './xbi.types';
import XBISchema from './xbi.schema';

const XBIModel = model<XBIDocument>('xbi', XBISchema);

export default XBIModel;
